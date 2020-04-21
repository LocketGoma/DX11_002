﻿//
// App.xaml.cpp
// App 클래스의 구현입니다.
//

#include "pch.h"
#include "DirectXPage.xaml.h"

using namespace DirectX11_002_ShootingGame;

using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
/// <summary>
/// Singleton 애플리케이션 개체를 초기화합니다. 이것은 실행되는 작성 코드의 첫 번째
/// 줄이며 따라서 main() 또는 WinMain()과 논리적으로 동일합니다. = 진입점
/// </summary>
App::App()
{
	InitializeComponent();
	Suspending += ref new SuspendingEventHandler(this, &App::OnSuspending);
	Resuming += ref new EventHandler<Object^>(this, &App::OnResuming);
}

/// <summary>
/// 최종 사용자가 애플리케이션을 정상적으로 시작할 때 호출됩니다. 다른 진입점은
/// 특정 파일을 열거나, 검색 결과를 표시하는 등 애플리케이션을 시작할 때
/// 사용됩니다.
/// </summary>
/// <param name="e">시작 요청 및 프로세스에 대한 정보입니다.</param>
void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e)
{
#if _DEBUG
	if (IsDebuggerPresent())
	{
		DebugSettings->EnableFrameRateCounter = true;
	}
#endif

	auto rootFrame = dynamic_cast<Frame^>(Window::Current->Content);

	// 창에 콘텐츠가 이미 있는 경우 앱 초기화를 반복하지 말고,
	// 창이 활성화되어 있는지 확인하십시오.
	if (rootFrame == nullptr)
	{
		// 탐색 상황에 맞게 사용되는 프레임을 만들어 이를
		// SuspensionManager 키에 연결합니다.
		rootFrame = ref new Frame();

		rootFrame->NavigationFailed += ref new Windows::UI::Xaml::Navigation::NavigationFailedEventHandler(this, &App::OnNavigationFailed);

		// 현재 창에 프레임 넣기
		Window::Current->Content = rootFrame;
	}

	if (rootFrame->Content == nullptr)
	{
		// 탐색 스택이 복원되지 않으면 첫 번째 페이지로 돌아가고
		// 필요한 정보를 탐색 매개 변수로 전달하여 새 페이지를
		// 구성합니다.
		rootFrame->Navigate(TypeName(DirectXPage::typeid), e->Arguments);
	}

	if (m_directXPage == nullptr)
	{
		m_directXPage = dynamic_cast<DirectXPage^>(rootFrame->Content);
	}

	if (e->PreviousExecutionState == ApplicationExecutionState::Terminated)
	{
		m_directXPage->LoadInternalState(ApplicationData::Current->LocalSettings->Values);
	}
	
	// 현재 창이 활성 창인지 확인
	Window::Current->Activate();
}
/// <summary>
/// 애플리케이션 실행이 일시 중단된 경우 호출됩니다.  애플리케이션이 종료될지
/// 또는 메모리 콘텐츠를 변경하지 않고 다시 시작할지 여부를 결정하지 않은 채
/// 응용 프로그램 상태가 저장됩니다.
/// </summary>
/// <param name="sender">일시 중단 요청의 소스입니다.</param>
/// <param name="e">일시 중단 요청에 대한 세부 정보입니다.</param>
void App::OnSuspending(Object^ sender, SuspendingEventArgs^ e)
{
	(void) sender;	// 사용하지 않는 매개 변수
	(void) e;	// 사용하지 않는 매개 변수

	m_directXPage->SaveInternalState(ApplicationData::Current->LocalSettings->Values);
}

/// <summary>
/// 애플리케이션 실행이 다시 시작된 경우 호출됩니다.
/// </summary>
/// <param name="sender">다시 시작된 요청의 소스입니다.</param>
/// <param name="args">다시 시작 요청에 대한 정보입니다.</param>
void App::OnResuming(Object ^sender, Object ^args)
{
	(void) sender; // 사용하지 않는 매개 변수
	(void) args; // 사용하지 않는 매개 변수

	m_directXPage->LoadInternalState(ApplicationData::Current->LocalSettings->Values);
}

/// <summary>
/// 특정 페이지 탐색에 실패한 경우 호출됨
/// </summary>
/// <param name="sender">탐색에 실패한 프레임</param>
/// <param name="e">탐색 실패에 대한 정보</param>
void App::OnNavigationFailed(Platform::Object ^sender, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs ^e)
{
	throw ref new FailureException("Failed to load Page " + e->SourcePageType.Name);
}

