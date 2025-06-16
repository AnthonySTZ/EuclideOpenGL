#pragma once

#include "Node.h"
#include "Fields/FileField.h"

class ImportObj : public Node {

public:
	ImportObj() : Node("ImportObj") {
		inputsNb = 0;
		outputsNb = 1;

		parameters["Filename"] = std::make_unique<FileField>("File Name", std::set<std::string>{".obj"}, "");

		paramOrder.push_back("Filename");
	}

	Mesh& processOutput(uint32_t index, bool *updateDirty = nullptr) override;
	static Mesh readObj(std::string filename);
private: 
	Mesh cachedMesh;
};