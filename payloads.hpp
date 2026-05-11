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



namespace udp_payload {

inline constexpr uint8_t UPDATE_SPATIAL = 0;
inline constexpr uint8_t UPDATE_FIGHTER = 1;
inline constexpr uint8_t UPDATE_RELINK = 2;
inline constexpr uint8_t UPDATE_HIGH_PRECISION = 3;
inline constexpr uint8_t UPDATE_ITEM_RELINK = 4;
inline constexpr uint8_t UPDATE_ITEM = 5;

struct item_update {
	// 4 bytes
	int item_id;

	// 4 bytes
	uint8_t item_type;
	bool is_container;
	uint8_t contained_commodity;
	uint8_t padding[1];

	// 4 bytes
	int contained_amount;
};
static_assert(sizeof(item_update) == 12);

struct high_precision_update {
	// 4 bytes
	int spatial_entity_id;

	// 4 bytes
	float x;

	// 4 bytes
	float y;
};
static_assert(sizeof(high_precision_update) == 12);

struct spatial_update {
	// 4 bytes
	int spatial_entity_id;

	// 4 bytes
	int16_t x;
	int16_t y;

	// 4 bytes
	uint8_t direction;
	uint8_t padding[3];
};
static_assert(sizeof(spatial_update) == 12);

struct fighter_update {
	// 4 bytes
	int fighter_id;

	// 4 bytes
	int16_t hp;
	int16_t max_hp;

	// 4 bytes
	uint8_t energy;
	uint8_t attack_energy;
	uint8_t race;
	uint8_t weapon_type;
};
static_assert(sizeof(fighter_update) == 12);

struct relink_update {
	// 4 bytes
	int fighter_id;

	// 4 bytes
	int item_id;

	// 4 bytes
	uint8_t padding[4];
};
static_assert(sizeof(relink_update) == 12);

struct relink_item_update {
	// 4 bytes
	int item_id;

	// 4 bytes
	int spatial_id;

	// 4 bytes
	uint8_t padding[4];
};
static_assert(sizeof(relink_item_update) == 12);

struct udp_update {

	// 4 bytes
	uint8_t update_type;
	uint8_t padding[3];

	// 4 bytes
	int timestamp;

	// 4 bytes
	int sent_to_player;

	// 12 bytes
	union {
		spatial_update spatial;
		fighter_update fighter;
		relink_update relink;
		relink_item_update relink_item;
		high_precision_update high_precision;
		item_update item;
	} payload;
};
static_assert(sizeof(udp_update) == 24);

}