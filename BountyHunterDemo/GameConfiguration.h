///-------------------------------------------------------------------------------------------------
/// File:	GameConfiguration.h.
///
/// Summary:	Declares the game configuration class.
///-------------------------------------------------------------------------------------------------

#ifndef __GAME_CONFIG_H__
#define __GAME_CONFIG_H__


/// Summary:	The game title.
static constexpr const char*		GAME_TITLE							{ "BountyHunter Demo" };

/// Summary:	Width of the game window.
static constexpr unsigned int		GAME_WINDOW_WIDTH					{ 800 };

/// Summary:	Height of the game window.
static constexpr unsigned int		GAME_WINDOW_HEIGHT					{ 600 };

/// Summary:	True if game should start in fullscreen mode.
static constexpr bool				GAME_WINDOW_FULLSCREEN				{ false };

/// Summary:	Defines the delta time step the game simulation will be advanced per update.
static constexpr float				DELTA_TIME_STEP						{ 1.0f / 60.0f };

/// Summary:	The world up vector.
static constexpr float				WORLD_UP_VECTOR[2]					{ 0.0f, 1.0f };

/// Summary:	The world min and max bounds.
static constexpr float				WORLD_BOUND_MIN[2]					{ -100.0f, -100.0f };
static constexpr float				WORLD_BOUND_MAX[2]					{  100.0f,  100.0f };

/// Summary:	The default collector respawntime.
static constexpr size_t				MAX_PLAYERS							{ 4 };

/// Summary:	The default collector respawntime.
static constexpr float				DEFAULT_COLLECTOR_RESPAWNTIME		{ 5.0f }; // seconds

/// Summary:	The default bounty respawntime.
static constexpr float				DEFAULT_BOUNTY_RESPAWNTIME			{ 2.0f }; // seconds


#endif // __GAME_CONFIG_H__
