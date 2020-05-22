#include "ModLoader.h"
#include <vector>

using namespace std;

using namespace System;
using namespace System::Reflection;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace SharpboxAPI::Attributes;
using namespace SharpboxAPI::Events;

ref struct Mod
{
	// Mod Info
	SharpModAttribute^ info;
	// Mod assembly
	Assembly^ assembly;

	// Mod core, which contain all init message
	Object^ modCore;

	// Storage all managed mod object
	static List<Mod^>^ managedModList = gcnew List<Mod^>();
};

//Load assembly
Assembly^ LoadAssembly(string path)
{
	String^ sPath = gcnew String(path.c_str());
	auto assembly = Assembly::LoadFrom(sPath);
	return assembly;
}

void RegisterMod(std::string path)
{
	auto mod = gcnew Mod();

	auto modAssembly = LoadAssembly(path);
	mod->assembly = modAssembly;

	auto types = modAssembly->GetTypes();

	for (auto i = 0; i < types->Length; ++i)
	{
		auto type = types[i];
		auto attributes = type->GetCustomAttributes(SharpModAttribute::typeid, false);

		if (attributes->Length == 0 ||
			type->IsAbstract)
			continue;

		if (mod->info != nullptr)
		{
			// TODO: Warning: More than one mod info has found
			continue;
		}

		mod->info = safe_cast<SharpModAttribute^>(attributes[0]);
		mod->modCore = Activator::CreateInstance(type);
	}

	if (mod->info == nullptr)
	{
		// TODO: Warning: Not a mod
		return;
	}

	Mod::managedModList->Add(mod);
}

template<class Arg = void> void ExpandMessageArg(List<Object^>^ list) {}
template<class Arg, class... Args> void ExpandMessageArg(List<Object^>^ list, Arg p, Args... args)
{
	list->Add(p);
	ExpandMessageArg(list, args...);
}

template<class... Args> void SendMessage(Mod^ mod, string msg, Args... args)
{
	String^ sMsg = gcnew String(msg.c_str());

	auto type = mod->modCore->GetType();
	auto method = type->GetMethod(sMsg);
	if (method == nullptr)
		return;

	List<Object^>^ list = gcnew List<Object^>();
	ExpandMessageArg(list, args...);

	method->Invoke(mod->modCore, list->ToArray());
}

void ModPreInit()
{
	PreInit^ prerInitEvent = gcnew PreInit();
	prerInitEvent->modinfoList = gcnew List<SharpModAttribute^>();

	auto mods = Mod::managedModList;
	for (auto i = 0; i < mods->Count; ++i)
		prerInitEvent->modinfoList->Add(mods[i]->info);

	for (auto i = 0; i < mods->Count; ++i)
	{
		auto mod = mods[i];
		SendMessage(mod, "PreInit", prerInitEvent);
	}
}
