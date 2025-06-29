# Euclide WIP

Euclide is a node-based 3D engine currently in development.

## Nodes

![Image](./readme/interface.jpg?)

You can create new Node by right clicking on the graph (a dropdown list will appear).<br/>
You can cut node connections by holding the 'Y' key and draging on the connection.<br/>
You can delete nodes by selecting it and press 'Delete'.<br/>

I also added a caching system to avoid recalculating each node every time you update a node, but only the ones that are needed.

Current working nodes: (I will add more over time)<br/>
- **Primitive:**<br/>
    - **Cube**<br/>
    - **Grid**<br/>
    - **UvSphere**<br/>
    - **QuadSphere**<br/>
    - **Cylinder**<br/>
    - **Torus**<br/>
    - **Line**<br/>
    - **Circle**<br/>

- **Import:**<br/>
    - **ImportObj**<br/>

- **Point:**<br/>
    - **PointGenerate**</br>
    
- **Geometry:**<br/>
    - **Transform**<br/>
    - **Merge**<br/>
    - **Subdivide**<br/>
    - **SmoothNormals**<br/>
    - **HardenNormals**<br/>
    - **BoundingBox**<br/>
    - **FanTriangulate**<br/>

- **Copying:**<br/>
    - **CopyToPoints**<br/>
    - **Duplicate**<br/>

- **Utility:**<br/>
    - **VisualizeNormals**<br/>
    - **Null**<br/>

## Viewport

You can move with your mouse buttons (pan, zoom, orbit) in the scene.<br/>
There are some shortcuts :<br/>
- **F** to recenter the camera to the object.<br/>
- **G** to toogle the **grid** visibility.<br/>
- **W** to toogle the **wireframe** visibility.<br/>
- **P** to toogle the **polygons** visibility.<br/>
- **V** to toogle the **vertex** visibility.<br/>

## Parameters

When you select a node, there is a parameters tab that open.<br/>
You can change parameters value !