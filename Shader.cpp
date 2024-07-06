#define GLEW_STATIC
#include "Shader.h"
using namespace std;
//using namespace std::exception;
Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// 打开文件，但还并没有读到内存
	vShaderFile.open(vertexPath);
	fShaderFile.open(fragmentPath);

	//检查坏档
	vShaderFile.exceptions(std::ifstream::failbit|| std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);


	stringstream  vShaderStream;
	stringstream  fShaderStream;

	try {
		if (!vShaderFile.is_open()|| !fShaderFile.is_open())
		{
			throw std::exception("open file error");
		}

		// 读取文件的缓冲内容到数据流中
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vertexString = vShaderStream.str();
		fragmentString = fShaderStream.str();

		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		//cout<< vertexSource<<endl;
		//cout << fragmentSource << endl;

		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);

		checkCompileErrors(fragment, "FRAGMENT");
		//把着色器绑定到gl程序
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		checkCompileErrors(ID, "PROGRAM");
		//链接完之后可以把shader删掉
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	catch (const std::exception& ex)
	{
		printf(ex.what());
	}









	//std::stringstream vShaderStream, fShaderSt
}
void Shader::setInt(const std::string& name, int value) 
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(string name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x,y,z);
}
void Shader::setVec3(string name, glm::vec3& value)
{
		glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}
void Shader::setMat4(string name, glm::mat4& value)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::setFloat(string name, float x)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), x);
}
void Shader::use()
{
	glUseProgram(ID);
}

void Shader::checkCompileErrors(unsigned int ID, std::string type)
{
	int success;
	char infolog[512];

	if (type != "PROGRAM")
	{
		//编译错误
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			//番号id，给我多少id，传给我字符的长度,空数组地址
			glGetShaderInfoLog(ID, 512, NULL, infolog);
			cout << "shader compile error:" << infolog << endl;


		}
	}
		//连接错误
		else {
			glGetProgramiv(ID,GL_LINK_STATUS,&success);
			if (!success)
			{
				glGetShaderInfoLog(ID, 512, NULL, infolog);
				cout << "program link error:" << infolog << endl;
			}
		}
	
}

//void Shader::test()
//{
//	printf("test");
//}

//Shader::~Shader()
//{
//}
