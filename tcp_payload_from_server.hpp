/*
Payloads tailored for rare updates sent via tcp socket to players.
Used mostly for "responses" to "requests".
*/

#include <cstdint>

namespace tcp_payload {
constexpr inline uint8_t TCP_LOGIN = 0;
constexpr inline uint8_t TCP_FIGHTER = 1;

struct tcp_login_update{
	int player_id;

	uint8_t padding[4];

	uint8_t padding2[4];
};
static_assert(sizeof(tcp_login_update) == 12);

struct tcp_fighter_update{
	int fighter_id;

	int location_id;

	uint8_t race_id;
	uint8_t padding2[3];
};
static_assert(sizeof(tcp_fighter_update) == 12);

struct tcp_update{
	// 4 bytes
	uint8_t update_type;
	uint8_t padding[3];

	// 12 bytes
	union {
		tcp_login_update login;
		tcp_fighter_update fighter;
	} payload;
};
static_assert(sizeof(tcp_update) == 16);
}