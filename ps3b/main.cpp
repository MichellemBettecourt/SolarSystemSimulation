#include <sstream>
#include <iomanip>
#include <SFML/Audio.hpp>
#include "body.hpp"

int main(int argc, char* argv[])
{
  if (argc < 3)
  {
    std::cout << "Please enter a time and delta time" << std::endl;
    return -1;
  }
  std::vector<Body> planets;
  double window_size = 500.0;
  double time = atoi(argv[1]);
  double delta_time = atoi(argv[2]);
  sf::RenderWindow window(sf::VideoMode(window_size, window_size), "Window");
  window.setFramerateLimit(40);
  std::string data;
  int i = 0;
  double scale;
  while (std::getline(std::cin, data))
  {
    switch (i)
    {
      case (0):
        break;
      case (1):
        {
          scale = atof(data.c_str());
          Body planet(window_size, scale);
          std::cin >> planet;
          planets.push_back(planet);
          i++;
        }
        break;
      case (7):
        break;
      case (8):
        break;
      case(9):
        break;
      default:
        {
          Body planet(window_size, scale);
          std::cin >> planet;
          planets.push_back(planet);
        }
        break;
      }
    i++;
  }

  sf::Clock clock;
  int timer = 0;
  sf::Music music;
  if (!music.openFromFile("2001.wav"))
  {
    std::cout << "Failed to load music." << std::endl;
  }
  music.play();
  while (window.isOpen())
  {
      if (timer >= time)
      {
        break;
      }
      sf::Event event;
      while (window.pollEvent(event))
      {
        if (event.type == sf::Event::Closed)
          window.close();
      }
      window.clear();
      planets[0].step(planets, 0, delta_time);
      for (unsigned int i = 0; i < planets.size(); i++)
      {
        window.draw(planets[i]);
      }
      window.display();
      timer += delta_time;
  }

  std::cout << "Final State of Universe Output:" << std::endl;
  for (unsigned int u = 0; u < planets.size(); u++)
  {
    std::cout << " "
    << planets[u].get_x_coordinate()
    << "  "
    << planets[u].get_y_coordinate()
    << "  "
    << planets[u].get_x_velocity()
    << "  "
    << planets[u].get_y_velocity()
    << "  "
    << planets[u].get_mass()
    << "  "
    << planets[u].get_filename()
    << std::endl;
  }

  return 0;
}
