// Win32Project1.cpp : ¶¨ÒåÓ¦ÓÃ³ÌÐòµÄÈë¿Úµã¡£
//
#include "stdafx.h"
#include "Win32Project1.h"
#include <iostream>
#include <wingui.h>
#include "DelegateTest.h"
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <xutility>
#include <sstream>
#include <iosfwd>
#include <istream>
#include <Core.h>
#include <utils/FileUtil.h>
#include <utils/string_util.h>
#include <utils/CSVParser.h>
#include <Delegate.h>
#include <windows/Controls/buttons/CheckBox.h>
#include <windows/Controls/buttons/RadioButton.h>
#include <windows/Controls/buttons/PushButton.h>
#include <windows/Controls/Combox/ComboBox.h>
#include <windows/Controls/Combox/ComboBoxEx.h>
#include <reflect/property.h>
#include <Core.h>
#include <reflect/function.h>
#include <reflect/class.h>
#include <reflect/reflectSystem.h>
#include <reflect/object.h>

#if 1
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

using namespace Core;

class MyApp : public WinGUI::ApplicationBase
{
public:
	MyApp() 
		:WinGUI::ApplicationBase()
	{
	
	}
	~MyApp() {}
};


class MyDlg : public WinGUI::Dialog
{
public:
		
	using WinGUI::Dialog::Dialog;
protected:
	virtual bool OnCreate() override
	{
		if (Super::OnCreate())
		{
			CreateSubWindow<WinGUI::Button>("btn1", 200, 10, 100, 40, this, GetHandle());
			CreateSubWindow<WinGUI::Button>("btn2", 300, 10, 100, 40, this, GetHandle());
			CreateSubWindow<WinGUI::Button>("btn3", 400, 10, 100, 40, this, GetHandle());

			FindSubWindow<WinGUI::Button>("btn1")->SetText(TEXT("btn1"));
			FindSubWindow<WinGUI::Button>("btn1")->GetOnClick().AddLambda([this](){
				//MessageBox(GetHandle(), TEXT("Click Button 1"), TEXT(""), MB_OK);
				//FindSubWindow<WinGUI::CheckBox>("checkbox")->SetCheck(true);
				FindSubWindow<WinGUI::ComboBox>("Combox")->ShowDropdown();
			});

			FindSubWindow<WinGUI::Button>("btn2")->SetText(TEXT("btn2"));
			FindSubWindow<WinGUI::Button>("btn2")->GetOnClick().AddLambda([]() {
				MessageBox(NULL, TEXT("Click Button 2"), TEXT(""), MB_OK);
			});
			FindSubWindow<WinGUI::Button>("btn3")->SetText(TEXT("btn3"));
			FindSubWindow<WinGUI::Button>("btn3")->GetOnClick().AddLambda([]() {
				MessageBox(NULL, TEXT("Click Button 3"), TEXT(""), MB_OK);
			});

			CreateSubWindow<WinGUI::CheckBox>("checkbox", 200, 110, 100, 40, this, GetHandle());
			//FindSubWindow<WinGUI::CheckBox>("checkbox")->AutoCheck(false);
			FindSubWindow<WinGUI::CheckBox>("checkbox")->GetOnCheckBoxSelChanged().AddLambda([](bool bInCheck) {
				MessageBox(NULL, bInCheck ? TEXT("Checked") : TEXT("UnChecked"), TEXT(""), MB_OK);
			});

			CreateRadioButtonGroup("radioGroup")
				.AddRadioButton(TEXT("man"), 300, 110, 100, 40, this, GetHandle())
				.AddRadioButton(TEXT("female"), 400, 110, 100,40,this, GetHandle())
				.GetOnRadioButtonSelChanged().AddLambda([this](i32 InSelIndex) {
					MessageBox(GetHandle(), InSelIndex == 0 ? TEXT("man") : TEXT("female"), TEXT(""), MB_OK);
				})
				;
			CreateSubWindow<WinGUI::PushButton>("pushButton", 100, 210, 100, 40, this, GetHandle());

			auto& combox = CreateSubWindow<WinGUI::ComboBox>("Combox", 200, 210, 100, 200, this, GetHandle())
				->AddItem(TEXT("测试1"))
				.AddItem(TEXT("测试2"))
				.AddItem(TEXT("测试3"))
				.AddItem(TEXT("超长文本。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。"))
				.InsertItem(0,TEXT("插入0"))
				.DeleteItem(1)
				.SetItemHeight(30)
				.SetText(TEXT("SetText"))
				.SetLimit(1)
				.SelectItem(0,false)
				;
			combox.GetOnComboBoxSelChanged().AddLambda([](i32 InSelItemIndex) {
				//WinGUI::ShowMessageBox(std::to_wstring(InSelItemIndex));
			});

			auto& comboBoxEx = CreateSubWindow<WinGUI::ComboBoxEx>("ComboxEx", 300, 210, 100, 200, this, GetHandle())
				->AddItem(TEXT("ComboxEx 测试1"))
				.AddItem(TEXT("ComboxEx 测试2"))
				.AddItem(TEXT("ComboxEx 测试3"))
				;
			
			//WinGUI::ShowMessageBox(std::to_wstring(combox.GetItemHeight()));
			//WinGUI::ShowMessageBox(std::to_wstring(combox.GetExtendedUI()));

			//combox.ClearAllItems();

			//combox.SetEditCtrlSel(0, -1);
			//i32 selStartPos, selEndPos;
			//combox.GetEditCtrlSel(selStartPos, selEndPos);
			//WinGUI::ShowMessageBox(std::to_wstring(selStartPos));
			//WinGUI::ShowMessageBox(std::to_wstring(selEndPos));

			//WinGUI::ShowMessageBox(std::to_wstring(combox.FindItem(TEXT("超长文本"))));

		}
		return true;
	}
};

class C : public Core::Object
{
	DECLARE_OBJECT(,C,Core::Object)
public:

	void testA() {
		++b;
	}

	int testB() {
		a += 10;
		return a;
	}
	f32 testC() {
		return f;
	}
	int a = 1000;
	int b = 10000;
	f32 f = 1.2341f;
};

IMPLEMENT_OBJECT_BEGIN(C, Core::Object)
DEFINE_PROPERTY(C, a)
DEFINE_PROPERTY(C, b)

DEFINE_FUNCTION(C, void, testA)
DEFINE_FUNCTION(C, i32, testB)
DEFINE_FUNCTION(C, f32, testC)
IMPLEMENT_OBJECT_END()


typedef void(*Func1)();
typedef void(Object::*Func2)();

int APIENTRY wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR    lpCmdLine,
	int       nCmdShow)
{
	
	C myC;

	auto testFunc = &C::testA;
	auto pTestFunc = (void*)&testFunc;
	Func2 pTestFunc2;
	
	memcpy(&pTestFunc2, &testFunc, sizeof(testFunc));
	auto myCC = myC.GetClass();

	auto ValueA = myC.GetValue<i32>("a");
	myC.SetValue("a", 10000);
	ValueA = myC.GetValue<i32>("a");
	myC.SetValue("b", 10);
	auto ValueB = myC.GetValue<i32>("b");

	myC.CallFunction<void>("testA");
	auto b = myC.CallFunction<i32>("testB");
	auto f = myC.CallFunction<f32>("testC");

	auto pClass = IReflectSystem::GetInst()->FindClass("class C");
	//auto scv = CSVParser::Create(TEXT("F:/GameDemo/Content/Configs/Skills.csv"));

	auto propA = pClass->FindProp("a");
	auto propB = pClass->FindProp("b");

	auto pClassO = Core::Object::StaticClass();
	auto pClassC = C::StaticClass();
	
	WinGUI::AppWrapper<MyApp> app;
	auto dlg = app->CreateTopWindow<MyDlg>(100, 100, 800, 600,nullptr);
	dlg->Show();
	

#if 0
	auto dlg1 = app->CreateTopWindow<MyDlg>(200, 200, 800, 600);
	dlg1->SetText(TEXT("dlg1"));
	dlg1->Show();
#endif

	app->SetMainFrameWindow(dlg->GetHandle());
	app->Run();

	return 0;
}


