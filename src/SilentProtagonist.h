#pragma once

namespace SilentProtagonist
{
	// Relocations for Addresses
	REL::Relocation<uintptr_t> hookSilentGetterRelocation(REL::ID(2229972));
	REL::Relocation<uintptr_t> hookTimerSet1Relocation(REL::ID(2229974), REL::Offset(0xCAD));
	REL::Relocation<uintptr_t> hookTimerSet2Relocation(REL::ID(2230178), REL::Offset(0xED));
	REL::Relocation<uintptr_t> qword01Relocation(REL::ID(4798212));
	REL::Relocation<uintptr_t> qword02Relocation(REL::ID(981895));

	extern "C"
	{
		// Silent File
		const char* silentFileLocation = "data\\sound\\voice\\xxx_placeholder_silence.wav";

		// Addresses
		uintptr_t qword01Address = qword01Relocation.address();
		uintptr_t qword02Address = qword02Relocation.address();

		// Assembly Hooks
		void* __fastcall HookSilentGetter(void);
		void* __fastcall HookTimerSet1(void);
		void* __fastcall HookTimerSet2(void);
	}

	inline bool Install(const F4SE::LoadInterface* a_f4se)
	{
		REX::INFO("Installing Hooks");

		// Get F4SE Version
		REL::Version F4SEVersion = a_f4se->F4SEVersion();

		// Log F4SE Version
		REX::INFO(std::string("F4SE Version: ") + F4SEVersion.string());

		// Get the Trampoline
		auto& trampoline = REL::GetTrampoline();

		// Allocate
		trampoline.create(64);

		// Write a Call for HookSilentGetter
		trampoline.write_call<5>(hookSilentGetterRelocation.address(), (uintptr_t)&HookSilentGetter);

		// Write a Call for HookTimerSet1
		trampoline.write_call<5>(hookTimerSet1Relocation.address(), (uintptr_t)&HookTimerSet1);
		REL::WriteSafe(hookTimerSet1Relocation.address() + 0x5, (void*)"\x90\x90\x90", 0x3);

		// Write a Call for HookTimerSet2
		trampoline.write_call<5>(hookTimerSet2Relocation.address(), (uintptr_t)&HookTimerSet2);
		REL::WriteSafe(hookTimerSet2Relocation.address() + 0x5, (void*)"\x90\x90\x90\x90\x90\x90\x90\x90", 0x8);

		REX::INFO("Hooks Installed");
		return true;
	}
}
