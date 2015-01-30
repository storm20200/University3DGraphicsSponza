#include "SceneModel.h"



// Engine headers.
#include <SceneModel/Mesh.hpp>



// Personal headers.
#include <Misc/Vertex.h>



namespace util
{
    void calculateVBOSize (const std::vector<SceneModel::Mesh>& meshes, size_t& vertexSize, size_t& elementSize)
    {
        // Create temporary accumlators.
        size_t vertices { 0 }, elements { 0 };  

        // We need to loop through each mesh adding up as we go along.
        for (const auto& mesh : meshes)
        {
            vertices += mesh.getPositionArray().size();
            elements += mesh.getElementArray().size();
        }

        // Calculate the final values.
        vertexSize = vertices * sizeof (Vertex);
        elementSize = elements * sizeof (unsigned int);
    }


    void assembleVertices (std::vector<Vertex>& vertices, const SceneModel::Mesh& mesh)
    {
        // Obtain each attribute.
        const auto& positions       = mesh.getPositionArray();
        const auto& normals         = mesh.getNormalArray();
        const auto& texturePoints   = mesh.getTextureCoordinateArray();

        // Check how much data we need to allocate.
        const auto size             = positions.size();
        vertices.resize (size);

        // Fill the actual data.
        for (unsigned int i = 0; i < size; ++i)
        {
            vertices[i] = { positions[i], normals[i], texturePoints[i] };
        }
    }
}