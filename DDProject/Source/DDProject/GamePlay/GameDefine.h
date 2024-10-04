#pragma once

UENUM()
enum class ETableType : uint8
{
	BPResource = 0,
};

UENUM()
enum class ESceneType : uint8
{
	Test = 0,
	Lobby = 1,
};

UENUM()
enum class EPlayerState : uint8
{
	Default = 0,
	Climb = 1,
};
