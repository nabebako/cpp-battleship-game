#include <vector>
#include <array>
#include <memory>

void pause(const double& secs);

enum class TileStatus
{
	unknown,
	hit,
	miss,
};

enum class Rotation
{
	horizontal,
	vertical,
};

struct coordinate
{
	unsigned int x;
	unsigned int y;
};

template<unsigned int size>
class Board
{
private:
	std::array<TileStatus, size * size> map;
	unsigned int mapSize;

public:
    Board():
		mapSize(size)
	{
		map.fill(TileStatus::unknown);
	}

    void render() const
	{
		for (size_t i = 0, i < map.size(); i++)
		{
			if (i % mapSize == 0)
				std::cout << '\n';

			switch (map.at(i))
			{
			case TileStatus::unknown:
				std::cout << 'o';
				break;

			case TileStatus::hit:
				std::cout << 'x';
				break;

			case TileStatus::miss:
				std::cout << '-';
				break;
			
			default:
				break;
			}
		}
	}

    void edit(int& edit_x, int& edit_y);
    void editHit(int& edit_x, int& edit_y);
    void editTimeup();
};

class Target
{
private:
	void locate(const int& limit_x, const int& limit_y, const Space& spcace);

public:
	Target(coordinate pos, const unsigned int size, const Rotation rotation);

    void damage();
    int health;
	coordinate pos;
	unsigned int length;
	Rotation rotation;
    bool is_destroyed = false;
};