//alien code. NEED TO DELETE AND WRITE ANOTHER
#pragma once
#include <vector>
#include <array>
#include <string>
#include <QOpenGLTexture>

struct Texture final
{
    std::string type;
    std::string path;
    QOpenGLTexture* texture;
};
struct Vertex
{
	std::array<float, 3> vertex;
	std::array<float, 3> normal;
	std::array<float, 3> color;
	std::array<float, 2> TexCoords;
	// tangent
	std::array<float, 3> Tangent;
	// bitangent
	std::array<float, 3> Bitangent;
};

class Mesh final
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Mesh() = default;
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    {
        this->vertices = vertices;
        this->indices = indices;
    }
};