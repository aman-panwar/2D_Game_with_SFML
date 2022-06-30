#include "planc.h"
Planc::Planc()
{
    //planc texture
    switch (gameData->getPlancStyle())
    {
    case PlancStyle::Style1:
        object.setTexture(gameData->getTextureHolder().get(TextureID::Planc1));
        break;
    case PlancStyle::Style2:
        object.setTexture(gameData->getTextureHolder().get(TextureID::Planc2));
        break;
    default:
        object.setTexture(gameData->getTextureHolder().get(TextureID::Planc1));
        break;
    };

    //object.setTextureRect(sf::IntRect(0,0,DEFAULT_PLANC_WIDTH,PLANC_HEIGHT));
    object.setScale(DEFAULT_PLANC_WIDTH / object.getLocalBounds().width,
                    PLANC_HEIGHT / object.getLocalBounds().height);
    //postion
    object.setOrigin(object.getLocalBounds().width / 2, object.getLocalBounds().height / 2);
    object.setPosition(
        sf::Vector2f(gameData->getWindow()->getSize().x / 2,
                     gameData->getWindow()->getSize().y - PLANC_DIST_FROM_BOTTOM - object.getLocalBounds().height / 2));

    //velocity
    velocity = sf::Vector2f(0.f, 0.f);
}
void Planc::activateMomentum()
{
    momentumEndTime = sf::Time(sf::seconds(MOMENTUM_TIME));
    myClock.restart();
}
void Planc::update(sf::Time deltaTime)
{
    object.move(velocity * deltaTime.asSeconds());

    auto object_size = object.getLocalBounds();
    object_size.width *= object.getScale().x;
    object_size.height *= object.getScale().y;

    //handeling collison with walls
    float right_boundary_cord = gameData->getWindow()->getSize().x / 2.0 + LEVEL_WIDTH / 2.0,
          left_boundary_cord = gameData->getWindow()->getSize().x / 2.0 - LEVEL_WIDTH / 2.0,
          planc_y_cord = gameData->getWindow()->getSize().y - PLANC_DIST_FROM_BOTTOM - PLANC_HEIGHT / 2.0,
          planc_left_x_cord = object.getPosition().x - object_size.width / 2,
          planc_right_x_cord = object.getPosition().x + object_size.width / 2;

    ////std::cout<<<<object.getPosition().x<<" "<<object.getPosition().y<<'\n';

    if (planc_right_x_cord >= right_boundary_cord)
    {
        object.setPosition(sf::Vector2f(right_boundary_cord - object_size.width / 2.0, planc_y_cord));
        velocity.x = 0;
    }
    if (planc_left_x_cord <= left_boundary_cord)
    {
        object.setPosition(sf::Vector2f(left_boundary_cord + object_size.width / 2.0, planc_y_cord));
        velocity.x = 0;
    }

    if (myClock.getElapsedTime() < momentumEndTime)
    {
        velocity.x = velocity.x != 0 ? (abs(velocity.x) - MOMENTUM_RETARDATION) * velocity.x / abs(velocity.x) : 0;
        velocity.y = 0;
    }
    else
    {
        velocity.x = 0;
        velocity.y = 0;
    }
}
void Planc::draw()
{
    auto window = gameData->getWindow();
    window->draw(object);
}
void Planc::move(Dir direction, bool isPressed)
{
    auto object_size = object.getLocalBounds();
    object_size.width *= object.getScale().x;
    object_size.height *= object.getScale().y;
    float right_boundary_cord = gameData->getWindow()->getSize().x / 2.0 + LEVEL_WIDTH / 2.0,
          left_boundary_cord = gameData->getWindow()->getSize().x / 2.0 - LEVEL_WIDTH / 2.0,
          //planc_y_cord = gameData->getWindow()->getSize().y - PLANC_DIST_FROM_BOTTOM - PLANC_HEIGHT / 2.0,
          planc_left_x_cord = object.getPosition().x - object_size.width / 2,
          planc_right_x_cord = object.getPosition().x + object_size.width / 2;

    velocity.x = cur_speed * (2 * (direction == Dir::Right) - 1);
    last_dir = (2 * (direction == Dir::Right) - 1);
    if ((!isPressed) ||
        ((planc_right_x_cord >= right_boundary_cord) && (direction == Dir::Right)) ||
        ((planc_left_x_cord <= left_boundary_cord) && (direction == Dir::Left)))
    {
        last_dir = 0;
    }
    velocity.y = 0.f;
}
void Planc::increaseSpeed()
{
    cur_speed = std::min(cur_speed + PLANC_SPEED_CHANGE, float(MAX_PLANC_SPEED));
}
void Planc::decreaseSpeed()
{
    cur_speed = std::max(cur_speed - PLANC_SPEED_CHANGE, float(MIN_PLANC_SPEED));
}
void Planc::increaseLength()
{
    float target_size = std::min(float(MAX_PLANC_WIDTH), object.getLocalBounds().width + PLANC_WIDTH_CHANGE);
    object.setScale(target_size / object.getLocalBounds().width, 1);
}
void Planc::decreaseLength()
{
    float target_size = std::max(float(MIN_PLANC_WIDTH), object.getLocalBounds().width - PLANC_WIDTH_CHANGE);
    object.setScale(target_size / object.getLocalBounds().width, 1);
}
sf::Vector2f Planc::getVelocity()
{
    return sf::Vector2f(last_dir * cur_speed, 0);
}
sf::FloatRect Planc::getBounds()
{
    return object.getGlobalBounds();
}