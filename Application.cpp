#include "Application.h"
#include <iostream>
#include <string>

namespace App
{
    //选中结果
    bool isShowDrag = false;
    //字符串结果
    std::string text = "";
    //拖拽值
    float fValue = 0.5f;

    void RenderUI()
    {
        //创建一个设置窗口
        ImGui::Begin("设置拖拽按钮");
        //按钮在单击时返回true（大多数小部件在编辑/激活时返回true）
        if (ImGui::Button("按钮"))
        {
            //单击事件处理程序
        }
        //显示一些文本（也可以使用字符串格式）
        ImGui::Text("这是一个中文字符串");

        // 缓冲区用于存储文本输入值
        char buffer[256] = "";
        ImGui::InputText("输入框", buffer, sizeof(buffer));
        //编码转换
        std::string textU8 = buffer;

        ImGui::Checkbox("显示拖拽", &isShowDrag);
        if (isShowDrag)
        {
            float value = 10.0f;
            ImGui::DragFloat(u8"值", &value);
        }
        //使用从0.0f到1.0f的滑块编辑1个浮动
        ImGui::SliderFloat("float", &fValue, 0.0f, 1.0f);
        ImGui::SameLine();
        ImGui::Text("Value %f", fValue);
        ImGui::End();
    }
}
