#pragma once

#ifdef VUSE_PLATFORM_WINDOWS

extern Vuse::Application* Vuse::CreateApplication();

int main( int argc, char** argv )
{
	Vuse::Log::Init();

	Vuse::Application* app = Vuse::CreateApplication();
	app->Run();
	delete app;
}

#endif
