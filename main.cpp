#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

using namespace std;

// function declatrations
void createCircle(const string &, float, float, float, vector<shared_ptr<sf::Shape>> &);
void createRectangle(const string &, float, float, float, float, vector<shared_ptr<sf::Shape>> &);

int main()
{
    string shapeName, shapeType;
    float radius, length, breadth, x_pos, y_pos, x_speed, y_speed;
    ifstream fin("config.txt");
    vector<shared_ptr<sf::Shape>> m_Shapes; // polymorphism
    vector<sf::Vector2f> speeds;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window;
    window.create(sf::VideoMode(800, 800), "SFML", sf::Style::Default, settings);

    // check the file state

    if (!fin.is_open())
    {
        cout << "Error while opening the file\n";
        return -1;
    }
    while (fin >> shapeType)
    {
        if (shapeType == "Circle")
        {
            fin >> shapeName >> radius >> x_pos >> y_pos >> x_speed >> y_speed;
            createCircle(shapeName, radius, x_pos, y_pos, m_Shapes);
            sf::Vector2f s;
            s.x = x_speed;
            s.y = y_speed;
            speeds.push_back(s);
        }
        if (shapeType == "Rectangle")
        {
            fin >> shapeName >> length >> breadth >> x_pos >> y_pos >> x_speed >> y_speed;
            createRectangle(shapeName, length, breadth, x_pos, y_pos, m_Shapes);
            sf::Vector2f s;
            s.x = x_speed;
            s.y = y_speed;
            speeds.push_back(s);
        }
    }
    fin.close();

    while (window.isOpen())
    {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update the game world
        for (int i = 0; i < m_Shapes.size(); i++)
        {
            if ((*m_Shapes[i]).getPosition().x <= 0 || (*m_Shapes[i]).getPosition().x + (*m_Shapes[i]).getLocalBounds().width >= window.getSize().x)
                speeds[i].x *= -1;
            if ((*m_Shapes[i]).getPosition().y <= 0 || (*m_Shapes[i]).getPosition().y + (*m_Shapes[i]).getLocalBounds().height >= window.getSize().y)
                speeds[i].y *= -1;

            m_Shapes[i]->setPosition(m_Shapes[i]->getPosition() + speeds[i]); // adding two vectors together
        }

        // Draw the updated game world
        window.clear();
        // for (auto &shape : m_Shapes)
        // {
        //     window.draw(*shape);
        // }
        for (int i = 0; i < m_Shapes.size(); i++)
        {
            window.draw(*(m_Shapes[i]));
            // cout<<"get Local Bounds: "<<m_Shapes[i]->getLocalBounds().width<<" "<<(*m_Shapes[i]).getLocalBounds().height<<"\n";
        }
        window.display();
    }

    return 0;
}

void createCircle(const string &name, float rad, float x, float y, vector<shared_ptr<sf::Shape>> &m_shapes)
{
    shared_ptr<sf::Shape> circle = make_shared<sf::CircleShape>(rad); // this is polymorphism
    /*
    Yes, in C++, a base class pointer array can store pointers to objects of derived classes. This is a fundamental feature of object-oriented programming in C++ known as polymorphism.
    */
    // shared_ptr<sf::CircleShape> circle = make_shared<sf::CircleShape>(rad);
    //  shared_ptr<sf::CircleShape> circle;
    circle->setPosition(sf::Vector2f(x, y));
    m_shapes.push_back(circle);
}

void createRectangle(const string &name, float l, float b, float x, float y, vector<shared_ptr<sf::Shape>> &m_shapes)
{
    shared_ptr<sf::Shape> rect = make_shared<sf::RectangleShape>(sf::Vector2f(l, b)); // this is polymorphism
    /*
    Yes, in C++, a base class pointer array can store pointers to objects of derived classes. This is a fundamental feature of object-oriented programming in C++ known as polymorphism.
    */
    // shared_ptr<sf::RectangleShape> rect = make_shared<sf::RectangleShape>(sf::Vector2f(l, b));
    rect->setPosition(sf::Vector2f(x, y));
    rect->setFillColor(sf::Color::Red);
    m_shapes.push_back(rect);
    cout << "Rectangle shape created and added to vector\n";
}

/*
    first open a window,
    create some variables to read from file
    read from file,
    Create functions to store shapes
    display images,
    add movements and collisiino to the screen borders,
    try to add collision in between the shapes
*/

/*
    Instead for running the file reading in to the game loop I should try to do it as separet function
    that is store all the shapes first then run the game loop it is loading the assests and play
    How to profile the code

*/