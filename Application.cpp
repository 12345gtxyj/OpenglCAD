#include "Application.h"
#include <iostream>
#include <string>

namespace App
{
    //ѡ�н��
    bool isShowDrag = false;
    //�ַ������
    std::string text = "";
    //��קֵ
    float fValue = 0.5f;

    void RenderUI()
    {
        //����һ�����ô���
        ImGui::Begin("������ק��ť");
        //��ť�ڵ���ʱ����true�������С�����ڱ༭/����ʱ����true��
        if (ImGui::Button("��ť"))
        {
            //�����¼��������
        }
        //��ʾһЩ�ı���Ҳ����ʹ���ַ�����ʽ��
        ImGui::Text("����һ�������ַ���");

        // ���������ڴ洢�ı�����ֵ
        char buffer[256] = "";
        ImGui::InputText("�����", buffer, sizeof(buffer));
        //����ת��
        std::string textU8 = buffer;

        ImGui::Checkbox("��ʾ��ק", &isShowDrag);
        if (isShowDrag)
        {
            float value = 10.0f;
            ImGui::DragFloat(u8"ֵ", &value);
        }
        //ʹ�ô�0.0f��1.0f�Ļ���༭1������
        ImGui::SliderFloat("float", &fValue, 0.0f, 1.0f);
        ImGui::SameLine();
        ImGui::Text("Value %f", fValue);
        ImGui::End();
    }
}
