#include "VisualizeNormals.h"

Mesh VisualizeNormals::processOutput(uint32_t index, bool *updateDirty)
{
    auto it = inputs.find(0);
    if (it == inputs.end()) return Mesh();

    bool isInputDirty = false;
    Mesh inputMesh = it->second->getInputNode()->processOutput(it->second->getInputIndex(), &isInputDirty);

    if (!isDirty() && !isInputDirty){
		if (updateDirty != nullptr) *updateDirty = false;
		return cachedMesh;
	} 

    for (auto& point: inputMesh.points){

        uint32_t nVertex = point.vertices.size();
        if (nVertex == 0) continue;

        glm::vec3 normal{0.0f};
        for (auto& vertexId: point.vertices){
            normal += inputMesh.vertices[vertexId].normal;
        }
        normal /= nVertex;
        
        Float3Attrib normalAttrib = Float3Attrib(glm::normalize(normal));

        point.attribs["Color"] = std::make_unique<Float3Attrib>(*point.getAttrib<Float3Attrib>("Normal", &normalAttrib));
        
        
    }

	cachedMesh = inputMesh;

	if (updateDirty != nullptr) *updateDirty = true;
	dirty = false;

    return cachedMesh;
}
