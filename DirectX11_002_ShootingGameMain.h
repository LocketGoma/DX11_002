﻿#pragma once
//https://docs.microsoft.com/ko-kr/windows/uwp/gaming/tutorial-game-rendering
#include "Common\StepTimer.h"
#include "Common\DeviceResources.h"
#include "Content\Sample3DSceneRenderer.h"
#include "Content\SampleFpsTextRenderer.h"

// 화면의 Direct2D 및 3D 콘텐츠를 렌더링합니다.
namespace DirectX11_002_ShootingGame
{
	class DirectX11_002_ShootingGameMain : public DX::IDeviceNotify
	{
	public:
		DirectX11_002_ShootingGameMain(const std::shared_ptr<DX::DeviceResources>& deviceResources);
		~DirectX11_002_ShootingGameMain();
		void CreateWindowSizeDependentResources();
		void StartTracking() { m_sceneRenderer->StartTracking(); }
		void TrackingUpdate(float positionX) { m_pointerLocationX = positionX; }
		void StopTracking() { m_sceneRenderer->StopTracking(); }
		bool IsTracking() { return m_sceneRenderer->IsTracking(); }
		void StartRenderLoop();
		void StopRenderLoop();
		Concurrency::critical_section& GetCriticalSection() { return m_criticalSection; }

		// IDeviceNotify
		virtual void OnDeviceLost();
		virtual void OnDeviceRestored();

	private:
		void ProcessInput();
		void Update();
		bool Render();
		void UpdateDynamics();

		// 디바이스 리소스에 대한 캐시된 포인터입니다.
		std::shared_ptr<DX::DeviceResources> m_deviceResources;

		// TODO: 사용자 콘텐츠 렌더러로 대체합니다.
		std::unique_ptr<Sample3DSceneRenderer> m_sceneRenderer;
		std::unique_ptr<SampleFpsTextRenderer> m_fpsTextRenderer;

		Windows::Foundation::IAsyncAction^ m_renderLoopWorker;
		Concurrency::critical_section m_criticalSection;

		// 렌더링 루프 타이머입니다.
		DX::StepTimer m_timer;

		// 현재 입력 포인터 위치를 추적합니다.
		float m_pointerLocationX;

		// 내부 부착 컨트롤 함수 등.

	};
}