#pragma once
#include <memory>
#include <vector>
#include <cstdint>
#include <functional>
#include "Type.h"
// #include <xdo.h> do NOT include xdo.h here, conflict

namespace wallpaper
{

#include "Utils/NoCopyMove.hpp"

class WallpaperGL : NoCopy,NoMove {
public:
    WallpaperGL();
    ~WallpaperGL();

	bool Init(void *get_proc_address(const char *));

    void LoadPkg(const std::string& path, const std::string& entry) {
		Load(path, entry);
	}
    void Render();//uint fbo, int width, int height);
    void Clear();
	void SetAssets(const std::string& path);
	void SetFlip(bool value);
	void SetMousePos(float x, float y) /*{m_mousePos = std::vector<float>({x,y});}*/;

	// call this after loaded
	void SetDefaultFbo(uint fbo, uint16_t w, uint16_t h);
	void SetFillMode(FillMode);

	uint32_t CurrentFps() const;
	uint8_t Fps() const;
	void SetFps(uint8_t value);
	void SetUpdateCallback(const std::function<void()>&);

	bool Loaded() const {return m_loaded;};

	void Start();
	void Stop();
	bool IsRunning() const;

	void OutGraphviz(const std::string& path);

	float Volume() const;
	bool Muted() const;
	void SetMuted(bool);
	void SetVolume(float);

	bool MouseInput() const { return m_mouseInput; }
	void SetMouseInput(bool b) { m_mouseInput = b; }
	int MouseInputMode() const { return m_mouseInputMode; }
	void SetMouseInputMode(int i) { m_mouseInputMode = i; }
	int MouseInPutScreen() const;
	void SetMouseInputScreen(int);
private:
    void Load(const std::string& path, const std::string& entry);
private:
	class impl;
    std::unique_ptr<impl> pImpl;

	std::string m_pkgPath;
	std::string m_assetsPath;

	bool m_inited {false};
	bool m_loaded {false};
	int m_framecount {0};
	std::vector<float> m_mousePos;
	void* m_xdo {nullptr}; // xdo*
	int m_screen_num {0}; //useless value
	bool m_mouseInput {true};
	int m_mouseInputMode {1};
	int m_mouseInputScreen {0};

	float m_aspect;
	FillMode m_fillMode {FillMode::ASPECTCROP};
};

}
