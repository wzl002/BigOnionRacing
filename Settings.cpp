#include "Settings.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include "KeyInput.h"

Setting Settings::g_ResWindowWidth("g_ResWindowWidth", "Width of program window in Windowed mode.", "640");
Setting Settings::g_ResWindowHeight("g_ResWindowHeight", "Height of program window in Windowed mode.", "480");
Setting Settings::g_ResWindowBits("g_ResWindowBits", "Bits of program window in Windowed mode.", "32");
Setting Settings::g_ResFullscreenWidth("g_ResFullscreenWidth", "Width of resolution in Fullscreen mode.", "1024");
Setting Settings::g_ResFullscreenHeight("g_ResFullscreenHeight", "Height of resolution in Fullscreen mode.", "768");
Setting Settings::g_ResFullscreenBits("g_ResFullscreenBits", "Bits of program window in Fullscreen mode.", "32");
Setting Settings::g_StartFullscreen("g_StartFullscreen", "Start the program in fullscreen mode.", "0");

//void Settings::AttachLogic(GameLogic* logic) { detail::m_logic = logic; }
void Settings::AttachInput(InputHandler* input) { detail::m_input = input; }

void Settings::LoadSettingsFromData(const vector<string>& data)
{
	if (data.empty())
		return;

	vector<string>::const_iterator it;
	for (it = data.begin(); it != data.end(); it++)
	{
		istringstream oss(*it);

		string line;
		while (std::getline(oss, line))
		{
			Utils::StripComments(line);

			Command command(line);
			CommandSystem::DoCommand(command);
		}
	}

}

const vector<string> Settings::SaveSettingsToData()
{
	vector<string> data;

	data.push_back("unbindall\n");
	CommandSystem::SettingsToCommandList(data);
	CommandSystem::BindingsToCommandList(data);

	return data;
}