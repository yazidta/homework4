#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <SFML/Audio.hpp>

class CustomRectangleShape : public sf::RectangleShape
{
public:
    CustomRectangleShape(sf::Vector2f size, sf::Vector2f position) : sf::RectangleShape(size)
    {
        setPosition(position);
    }
    void setSpeed(double x, double y, double r)
    {
        speed_x_ = x;
        speed_y_ = y;
        speed_r_ = r;
    }
   void set_bounds(double t, double b, double l, double r)
    {
        top_ = t;
        bottom_ = b;
        left_ = l;
        right_ = r;
    }
    void moveInDirection(const sf::Time &elapsed, const sf::Keyboard::Key &key)
    {
        sf::FloatRect bounds = getGlobalBounds();
        if(key == sf::Keyboard::Up && !(bounds.top <= 0.0))
        {
            move(0, -speed_y_ * elapsed.asSeconds());
        }
        else if(key == sf::Keyboard::Right && !(bounds.left >= right_ - bounds.width))
        {
            move(speed_x_ * elapsed.asSeconds(), 0);
        }
        else if(key == sf::Keyboard::Down && !(bounds.top >= bottom_ - bounds.height))
        {
            move(0, speed_y_ * elapsed.asSeconds());
        }
        else if(key == sf::Keyboard::Left && !(bounds.left <= 0.0))
        {
            move(-speed_x_ * elapsed.asSeconds(), 0);
        }
    }
    bool isClicked(sf::Vector2i &mouse_position)
    {
        sf::FloatRect bounds = getGlobalBounds();
        if(mouse_position.x >= bounds.left && mouse_position.x <= bounds.left + bounds.width
            && mouse_position.y >= bounds.top && mouse_position.y <= bounds.top + bounds.height)
        {
            return true;
        }
        return false;
    }
private:
    double speed_x_=0, speed_y_=0, speed_r_=0;
    double top_=0, bottom_=0, left_=0, right_=0;
};
void change_color(sf::RectangleShape &rectangle)
{
    rectangle.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
}
int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    CustomRectangleShape rectangle3(sf::Vector2f(180.0, 75.0), sf::Vector2f(100.0, 200.0));
    rectangle3.setSpeed(50, 150, 10);
    rectangle3.set_bounds(0, window.getSize().y, 0, window.getSize().x);
    rectangle3.setFillColor(sf::Color(50, 100, 155));
    sf::Clock clock;
    srand(time(NULL));
    sf::Music music ;
    if(!music.openFromFile("audio.ogg"))
        std::cerr << "Could not load audio" << std::endl;
    music.setVolume(50);
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            rectangle3.moveInDirection(elapsed, sf::Keyboard::Up);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            rectangle3.moveInDirection(elapsed, sf::Keyboard::Down);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            rectangle3.moveInDirection(elapsed, sf::Keyboard::Left);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            rectangle3.moveInDirection(elapsed, sf::Keyboard::Right);
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(event.type == sf::Event::MouseButtonPressed)
            {
                if(event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                    std::cout << "Mouse clicked: " << mouse_pos.x << ", " << mouse_pos.y << std::endl;
                    if(rectangle3.isClicked(mouse_pos))
                    {
                        change_color(rectangle3);
                    }
                }
            }
        }
//       std::srand(std::time(nullptr));

//        std::vector<CustomRectangleShape> rectangles;

//        for(int i=0; i<10; i++)
//        {
//            sf::Vector2f size(120.0, 60.0);
//            sf::Vector2f position(std::rand() % (window.getSize().x - 120), std::rand() % (window.getSize().y - 60));
//            rectangles.emplace_back(CustomRectangleShape(size, position));
//        }

//        for(auto &rec : rectangles)
//        {
//            rec.setFillColor(sf::Color(0, 255, 0));
//            rec.set_bounds(0, window.getSize().x, 0, window.getSize().y);
//            rec.setSpeed(100, 200, 10);
//        }

//        while (window.isOpen()) {



//            for(auto &rec : rectangles)
//            {
//                window.draw(rec);
//            }

//            window.display();
//        }





        window.clear(sf::Color::Black);
        window.draw(rectangle3);
        window.display();
    }
    return 0;
}
