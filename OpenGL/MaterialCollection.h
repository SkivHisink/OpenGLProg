#include <vector>
namespace MaterialCollection
{
	struct Material
	{
		std::vector<float> ambient;
		std::vector<float> diffuse;
		std::vector<float> specular;
		float shininess;
	};
	enum MaterialTypes
	{
		rNone,
		Emerald,
		Jade,
		Obsidian,
		Pearl,
		Ruby,
		Turquoise,
		Brass,
		Bronze,
		Chrome,
		Copper,
		Gold,
		Silver,
		Black_plastic,
		Cyan_plastic,
		Red_plastic,
		White_plastic,
		Yellow_plastic,
		Black_rubber,
		Cyan_rubber,
		Green_rubber,
		Red_rubber,
		White_rubber,
		Yellow_rubber,
		Super_material
	};

	struct MaterialCollection {
		float shiness = 128;
		std::vector<Material> material_collection = { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, shiness * 0.0f},
			{ {0.0215f, 0.1745f, 0.0215f}, {0.07568f, 0.61424f, 0.07568f}, {0.633f, 0.727811f, 0.633f}, shiness * 0.6f },
	   { {0.135f, 0.2225f, 0.1575f}, {0.54f, 0.89f, 0.63f}, {0.316228f, 0.316228f, 0.316228f}, shiness * 0.1f },
	   { {0.05375f, 0.05f, 0.06625f}, {0.18275f, 0.17f, 0.22525f}, {0.332741f, 0.328634f, 0.346435f}, shiness * 0.3f },
	   { {0.25f, 0.20725f, 0.20725f}, {1.0f, 0.829f, 0.829f}, {0.296648f, 0.296648f, 0.296648f}, shiness * 0.088f },
	   { {0.1745f, 0.01175f, 0.01175f}, {0.61424, 0.04136,0.04136}, {0.727811f, 0.626959f, 0.626959f}, shiness * 0.6f },
	   { {0.1f, 0.18725f, 0.1745f}, {0.396, 0.74151f, 0.69102}, {0.297254f, 0.30829f, 0.306678f}, shiness * 0.1f },
	   { {0.329412f, 0.223529f, 0.027451f}, {0.780392f, 0.568627f, 0.113725f}, {0.992157f, 0.941176f, 0.807843f}, shiness * 0.21794872f },
	   { {0.2125f, 0.1275f, 0.054f}, {0.714f, 0.4284f, 0.18144f}, {0.393548 ,0.271906 ,0.166721}, shiness * 0.2f },
	   { {0.25f, 0.25f, 0.25f}, {0.4f, 0.4f, 0.4f}, {0.774597f, 0.774597f, 0.774597f}, shiness * 0.6f },
	   { {0.19125f, 0.0735f, 0.0225f}, {0.7038f, 0.27048, 0.0828}, {0.256777, 0.137622f, 0.086014f}, shiness * 0.1f },
	   { {0.24725f, 0.1995f, 0.0745f}, {0.75164f,0.60648, 0.22648}, {0.628281f, 0.555802f, 0.366065f}, shiness * 0.4f},
	   { {0.19225f, 0.19225f, 0.19225f}, {0.50754f, 0.50754f, 0.50754}, {0.508273f, 0.508273f, 0.508273f}, shiness * 0.4f },
	   { {0.0f, 0.0f, 0.0f}, {0.01f,0.01f, 0.01f}, {0.50, 0.50 ,0.50}, shiness * 0.25f },
	   { {0.0f, 0.1f, 0.06f}, {0.0f,0.50980392 ,0.50980392}, {0.50196078f, 0.50196078f, 0.50196078f}, shiness * 0.25f },
	   { {0.0f, 0.0f, 0.0f}, {0.1f,0.35, 0.1}, {0.45 ,0.55, 0.45}, shiness * 0.25f },
	   { {0.0f, 0.0f, 0.0f}, {0.5f, 0.0, 0.0}, {0.7, 0.6 ,0.6}, shiness * 0.25f },
	   { {0.0f, 0.0f, 0.0f}, {0.55f, 0.55, 0.55}, {0.70 ,0.70, 0.70}, shiness * 0.25f },
	   { {0.0f, 0.0f, 0.0}, {0.5 ,0.5, 0.0}, { 0.60, 0.60, 0.50}, shiness * 0.25f },
	   { {0.02f, 0.02f, 0.02f}, {0.01, 0.01, 0.01}, {0.4, 0.4 ,0.4}, shiness * 0.078125f },
	   { {0.0f, 0.05f, 0.05f}, {0.4, 0.5 ,0.5}, {0.04, 0.7 ,0.7}, shiness * 0.078125f },
	   { {0.0f, 0.05f, 0.0f}, {0.4,0.5,0.4}, {0.04,0.7, 0.04}, shiness * 0.078125f },
	   { {0.05f, 0.0f, 0.0f}, {0.5,0.4,0.4}, {0.7, 0.04, 0.04}, shiness * 0.078125f },
	   { {0.05f, 0.05f, 0.05f}, {0.5,0.5,0.5}, {0.7f, 0.7f, 0.7f}, shiness * 0.078125f } ,
	   { {0.05f, 0.05f, 0.0f}, {0.5f, 0.5f, 0.4f}, {0.7f, 0.7f, 0.04f}, shiness * 0.078125f },
	   { {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}, shiness * 1.0f } };
	};
}