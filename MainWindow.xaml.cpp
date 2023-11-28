// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#include <fstream>
#include <stdexcept>
#include <iostream>

#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::WinUI3Pen::implementation
{
    MainWindow::MainWindow()
    {

        InitializeComponent();
        flag = false;
        px = 100;
        py = 100;
        mySize = 16;
        IsChecked = true;
    }


    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }


}

struct winrt::Windows::UI::Color myCol = winrt::Microsoft::UI::Colors::Green();
void winrt::WinUI3Pen::implementation::MainWindow::Slider_ValueChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs const& e)
{
    mySize = e.NewValue();
}


void winrt::WinUI3Pen::implementation::MainWindow::CanvasControl_PointerPressed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    flag = true;
}


void winrt::WinUI3Pen::implementation::MainWindow::CanvasControl_PointerReleased(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    flag = false;
    px = py = 0.0;
    vx.push_back(px);
    vy.push_back(py);
    col.push_back(myCol);
    size.push_back(mySize);
}


void winrt::WinUI3Pen::implementation::MainWindow::CanvasControl_PointerMoved(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Input::PointerRoutedEventArgs const& e)
{
    CanvasControl canvas = sender.as<CanvasControl>();
    px = e.GetCurrentPoint(canvas).Position().X;
    py = e.GetCurrentPoint(canvas).Position().Y;
    if (flag) {
        vx.push_back(px);
        vy.push_back(py);
      col.push_back(myCol);
      size.push_back(mySize);
        canvas.Invalidate();
    }
}


void winrt::WinUI3Pen::implementation::MainWindow::CanvasControl_Draw(winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasControl const& sender, winrt::Microsoft::Graphics::Canvas::UI::Xaml::CanvasDrawEventArgs const& args)
{
    CanvasControl canvas = sender.as<CanvasControl>();
    int n = vx.size();
    if(n<=2) return;
    for (int i = 1; i < n; i++) {
        if (vx[i] == 0 && vy[i] == 0) {
            i++; continue;
        }
        args.DrawingSession().DrawLine(vx[i - 1], vy[i - 1], vx[i], vy[i], col[i], size[i]);
        args.DrawingSession().FillCircle(vx[i - 1], vy[i - 1], size[i] / 2, col[i]);
        args.DrawingSession().FillCircle(vx[i], vy[i], size[i] / 2, col[i]);
    }
    canvas.Invalidate();

}


void winrt::WinUI3Pen::implementation::MainWindow::ColorPicker_ColorChanged(winrt::Microsoft::UI::Xaml::Controls::ColorPicker const& sender, winrt::Microsoft::UI::Xaml::Controls::ColorChangedEventArgs const& args)
{
    myCol = args.NewColor();
}


void winrt::WinUI3Pen::implementation::MainWindow::ToggleButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
  
        if (IsChecked)
        {
            IsChecked = false;
            ColorPicker().Label(L"Disabled");
            colorPanel1().Visibility(Visibility::Collapsed);
            colorPanel2().Visibility(Visibility::Collapsed);
        }
        else
        {
            IsChecked = true;
            ColorPicker().Label(L"Enabled");

            colorPanel1().Visibility(Visibility::Visible);
            colorPanel2().Visibility(Visibility::Visible);
        }
   }





void winrt::WinUI3Pen::implementation::MainWindow::MenuFlyoutItem_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
	vx.clear();
	vy.clear();
	col.clear();
	size.clear();
    flag = false;
    px = 100;
    py = 100;
    mySize = 16;

}

// 일관된 파일 경로, 파일 작업에 대한 오류 검사, 예외가 있는 C++ 표준 라이브러리 파일 I/O 사용 등 제안된 개선 사항이 통합


void winrt::WinUI3Pen::implementation::MainWindow::MenuFlyoutItem_Click_1(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    const char* filePath = "C:/Users/PC/source/repos/WinUI3Pen-master/WinUI3Pen-master/my.txt";

    try
    {
        // Saving data using C++ standard library file I/O
        std::ofstream outFile(filePath);
        if (outFile.is_open())
        {
            int num = vx.size();
            outFile << num << '\n';
            for (int i = 0; i < num; i++)
            {
                outFile << vx[i] << ' ' << vy[i] << ' ' << static_cast<int>(col[i].A) << ' '
                    << static_cast<int>(col[i].B) << ' ' << static_cast<int>(col[i].G) << ' '
                    << static_cast<int>(col[i].R) << ' ' << size[i] << '\n';
            }
            outFile.close();
            MessageBox(NULL, L"The File was opened\n", L"Hi", NULL);
        }
        else
        {
            throw std::runtime_error("Error opening file for writing");
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        MessageBox(NULL, L"The File was not opened\n", L"hi2", NULL);
    }
}

void winrt::WinUI3Pen::implementation::MainWindow::MenuFlyoutItem_Click_2(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    const char* filePath = "C:/Users/PC/source/repos/WinUI3Pen-master/WinUI3Pen-master/my.txt";

    try
    {
        // Loading data using C++ standard library file I/O
        std::ifstream inFile(filePath);
        if (inFile.is_open())
        {
            vx.clear();
            vy.clear();
            col.clear();
            size.clear();

            int num;
            float vx1, vy1, size1;
            int colA, colB, colG, colR;

            inFile >> num;
            for (int i = 0; i < num; i++)
            {
                inFile >> vx1 >> vy1 >> colA >> colB >> colG >> colR >> size1;
                vx.push_back(vx1);
                vy.push_back(vy1);
                myCol.A = static_cast<uint8_t>(colA);
                myCol.B = static_cast<uint8_t>(colB);
                myCol.G = static_cast<uint8_t>(colG);
                myCol.R = static_cast<uint8_t>(colR);
                col.push_back(myCol);
                size.push_back(size1);
            }
            inFile.close();
            CanvasControl_PointerReleased(NULL, NULL);
        }
        else
        {
            throw std::runtime_error("Error opening file for reading");
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        MessageBox(NULL, L"The File was not opened\n", L"hi2", NULL);
    }
}
void winrt::WinUI3Pen::implementation::MainWindow::MenuFlyoutItem_Click_3(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    this->Close();
}


void winrt::WinUI3Pen::implementation::MainWindow::MenuFlyoutItem_Click_4(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    myCol = winrt::Microsoft::UI::Colors::CornflowerBlue();
    mySize = 50;
}
