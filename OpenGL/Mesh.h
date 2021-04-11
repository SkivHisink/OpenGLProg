////alien code. NEED TO DELETE AND WRITE ANOTHER
//#pragma once
//#include <vector>
//#include <array>
//#include <string>
//#include <QOpenGLFunctions>
//#include <QOpenGLBuffer>
//#include <QOpenGLVertexArrayObject>
//#include <QOpenGLTexture>
//#include <QOpenGLShaderProgram>
//#include <QOpenGLBuffer>
//#include <vector>
//#include <QOpenGLVertexArrayObject>
//#include <QVector3D>
//#include <QGuiApplication>
//#include <QMatrix4x4>
//#include <QOpenGLShaderProgram>
//#include <QScreen>
//#include <QtMath>
//
//struct Texture final
//{
//    unsigned int id;
//    std::string type;
//    std::string path;
//    QOpenGLTexture* texture;
//};
//struct Vertex final
//{
//	std::array<float, 3> vertex;
//	std::array<float, 3> normal;
//	std::array<float, 3> color;
//	std::array<float, 2> TexCoords;
//	// tangent
//	std::array<float, 3> Tangent;
//	// bitangent
//	std::array<float, 3> Bitangent;
//};
//class Shader
//{
//public:
//    // the program ID
//    unsigned int ID;
//
//    // constructor reads and builds the shader
//    Shader(const char* vertexPath, const char* fragmentPath)
//    {
//        // 1. retrieve the vertex/fragment source code from filePath
//        std::string vertexCode;
//        std::string fragmentCode;
//        std::ifstream vShaderFile;
//        std::ifstream fShaderFile;
//        // ensure ifstream objects can throw exceptions:
//        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//        try
//        {
//            // open files
//            vShaderFile.open(vertexPath);
//            fShaderFile.open(fragmentPath);
//            std::stringstream vShaderStream, fShaderStream;
//            // read file's buffer contents into streams
//            vShaderStream << vShaderFile.rdbuf();
//            fShaderStream << fShaderFile.rdbuf();
//            // close file handlers
//            vShaderFile.close();
//            fShaderFile.close();
//            // convert stream into string
//            vertexCode = vShaderStream.str();
//            fragmentCode = fShaderStream.str();
//        }
//        catch (std::ifstream::failure& e)
//        {
//            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
//        }
//        const char* vShaderCode = vertexCode.c_str();
//        const char* fShaderCode = fragmentCode.c_str();
//        // 2. compile shaders
//        unsigned int vertex, fragment;
//        // vertex shader
//        vertex = glCreateShader(GL_VERTEX_SHADER);
//        glShaderSource(vertex, 1, &vShaderCode, NULL);
//        glCompileShader(vertex);
//        checkCompileErrors(vertex, "VERTEX");
//        // fragment Shader
//        fragment = glCreateShader(GL_FRAGMENT_SHADER);
//        glShaderSource(fragment, 1, &fShaderCode, NULL);
//        glCompileShader(fragment);
//        checkCompileErrors(fragment, "FRAGMENT");
//        // shader Program
//        ID = glCreateProgram();
//        glAttachShader(ID, vertex);
//        glAttachShader(ID, fragment);
//        glLinkProgram(ID);
//        checkCompileErrors(ID, "PROGRAM");
//        // delete the shaders as they're linked into our program now and no longer necessary
//        glDeleteShader(vertex);
//        glDeleteShader(fragment);
//    }
//    // use/activate the shader
//    void use()
//    {
//        glUseProgram(ID);
//    }
//    // utility uniform functions
//    void setBool(const std::string& name, bool value) const
//    {
//        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
//    }
//    void setInt(const std::string& name, int value) const
//    {
//        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
//    }
//    void setFloat(const std::string& name, float value) const
//    {
//        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
//    }
//};
//class Mesh final
//{
//public:
//    // mesh data
//    std::vector<Vertex>       vertices;
//    std::vector<unsigned int> indices;
//    std::vector<Texture>      textures;
//
//    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, QObject* f)
//    {
//        this->vertices = vertices;
//        this->indices = indices;
//        this->textures = textures;
//
//        setupMesh(f);
//    }
//    void Draw(Shader& shader)
//    {
//        unsigned int diffuseNr = 1;
//        unsigned int specularNr = 1;
//        for (unsigned int i = 0; i < textures.size(); i++)
//        {
//            glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
//            // retrieve texture number (the N in diffuse_textureN)
//            std::string number;
//            std::string name = textures[i].type;
//            if (name == "texture_diffuse")
//                number = std::to_string(diffuseNr++);
//            else if (name == "texture_specular")
//                number = std::to_string(specularNr++);
//
//            shader.setFloat(("material." + name + number).c_str(), i);
//            glBindTexture(GL_TEXTURE_2D, textures[i].id);
//        }
//        glActiveTexture(GL_TEXTURE0);
//
//        // draw mesh
//        vao->bind();
//        vbo->bind();
//
//        vbo->write(0, vertices.data(), vertices.size() * sizeof(float));
//        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
//
//        vao->release();
//       m_program->release();
//    }
//private:
//    //  render data
//    QOpenGLVertexArrayObject* vao = nullptr;
//    QOpenGLBuffer* vbo = nullptr;
//    QOpenGLBuffer* ibo = nullptr;
//    QOpenGLShaderProgram* m_program = nullptr;
//    void setupMesh(QObject* f)
//    {
//        vao = new QOpenGLVertexArrayObject(f);
//        vao->create();
//        vao->bind();
//
//        vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
//        vbo->create();
//        vbo->setUsagePattern(QOpenGLBuffer::DynamicDraw);
//        vbo->bind();
//        vbo->allocate(vertices.data(), vertices.size() * sizeof(float));
//
//        ibo = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
//        ibo->create();
//        ibo->setUsagePattern(QOpenGLBuffer::DynamicDraw);
//        ibo->bind();
//        ibo->allocate(indices.data(), indices.size() * sizeof(GLuint));
//
//        m_program->enableAttributeArray("posAttr");
//        m_program->setAttributeBuffer("posAttr", GL_FLOAT, 0, 3, 8 * sizeof(float));
//
//        m_program->enableAttributeArray("normal");
//        m_program->setAttributeBuffer("normal", GL_FLOAT, 3 * sizeof(float), 3, 8 * sizeof(float));
//        m_program->enableAttributeArray("aTexCoords");
//        m_program->setAttributeBuffer("aTexCoords", GL_FLOAT, 6 * sizeof(float), 2, 8 * sizeof(float));
//    }
//};