#pragma once
#include<string>
#include <glm/detail/type_vec.hpp>
#include <glm/glm.hpp>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;
class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	string vertexString;
	string fragmentString;
	const char* vertexSource;//const只要被指定就不能再被改变
	const char* fragmentSource;
	unsigned int ID;//shader Program ID
	void setVec3(string name,float x,float y,float z);
	void setVec3(string name, glm::vec3& value);
	void setMat4(string name, glm::mat4& value);
	void setFloat(string name, float x);
	void use();
	void setInt(const std::string& name, int value);
private:
	void checkCompileErrors(unsigned int ID, std::string type);

};

