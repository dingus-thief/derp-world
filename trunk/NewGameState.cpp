#include "NewGameState.h"

NewGameState* NewGameState::newGameState = NULL;

NewGameState::NewGameState(sf::RenderWindow* window, StateManager* mgr) : State(window, mgr)
{
    nameEdit = new TextEdit(300, 50, 175);
    startButton = new Button("Start!", 500, 400);

    background.SetTexture(rm.getImage("menuBackground.png"));
    fireIncrementer.SetTexture(rm.getImage("incrementer.png"));
    fireDecrementer.SetTexture(rm.getImage("decrementer.png"));
    iceIncrementer.SetTexture(rm.getImage("incrementer.png"));
    iceDecrementer.SetTexture(rm.getImage("decrementer.png"));
    energyIncrementer.SetTexture(rm.getImage("incrementer.png"));
    energyDecrementer.SetTexture(rm.getImage("decrementer.png"));

    nameText = rm.getText("Enter name: ", 25);
    fireSkillText = rm.getText("Fire skill: ", 25);
    iceSkillText = rm.getText("Ice skill: ", 25);
    energySkillText = rm.getText("Energy skill: ", 25);
    energyPointsText = rm.getText("1", 25);
    firePointsText = rm.getText("1", 25);
    icePointsText = rm.getText("1", 25);

    pointsLeftText = rm.getText("Points left: ", 25);
    pointsLeftText.SetPosition(100, 150);

    nameText.SetPosition(100, 50);

    fireSkillText.SetPosition(100, 200);
    firePointsText.SetPosition(350, 200);
    fireIncrementer.SetPosition(375, 195);
    fireDecrementer.SetPosition(375, 217);

    iceSkillText.SetPosition(100, 250);
    icePointsText.SetPosition(350, 250);
    iceIncrementer.SetPosition(375, 245);
    iceDecrementer.SetPosition(375, 267);

    energySkillText.SetPosition(100, 300);
    energyPointsText.SetPosition(350, 300);
    energyIncrementer.SetPosition(375, 295);
    energyDecrementer.SetPosition(375, 317);
}

NewGameState::~NewGameState()
{
    //dtor
}

void NewGameState::handle()
{
    sf::Event Event;
    while (window->PollEvent(Event))
    {
        nameEdit->handleEvent(Event, window);
        switch (Event.Type)
        {
            case sf::Event::Closed:
                window->Close();
                break;
            case sf::Event::MouseMoved:
                checkButtons(window->ConvertCoords(sf::Mouse::GetPosition(*window).x, 0).x, window->ConvertCoords(0, sf::Mouse::GetPosition(*window).y).y);
                break;
            case sf::Event::MouseButtonPressed:
                if(Event.MouseButton.Button == sf::Mouse::Left)
                    clicked(window->ConvertCoords(sf::Mouse::GetPosition(*window).x, 0).x, window->ConvertCoords(0, sf::Mouse::GetPosition(*window).y).y);
                break;
            default:
                break;
        }
    }
}

void NewGameState::update()
{
    firePointsText.SetString(sf::String(to_string(firePoints)));
    icePointsText.SetString(sf::String(to_string(icePoints)));
    energyPointsText.SetString(sf::String(to_string(energyPoints)));
    pointsLeftText.SetString(sf::String("Points left:  " + to_string(pointsLeft)));
    //firePointsText.SetString(sf::String(to_string(pointsLeft)));
}

void NewGameState::checkButtons(float x, float y)
{
    startButton->checkHL(x, y);
}

void NewGameState::clicked(float x, float y)
{
    if(startButton->isClicked(x, y) && pointsLeft == 0 && !nameEdit->getText().empty())
        stateManager->changeState(GameState::Instance(window, stateManager, "Data/Levels/coolio.tmx"));
    else if(startButton->isClicked(x, y))
        stateManager->changeState(GameState::Instance(window, stateManager, "Data/Levels/coolio2.tmx"));

    if(pointsLeft > 0)
    {
        pointsLeft--;
        if(fireIncrementer.GetGlobalBounds().Contains(sf::Vector2f(x, y)))
            firePoints++;
        else if(iceIncrementer.GetGlobalBounds().Contains(sf::Vector2f(x, y)))
            icePoints++;
        else if(energyIncrementer.GetGlobalBounds().Contains(sf::Vector2f(x, y)))
            energyPoints++;
        else pointsLeft++;
    }

    pointsLeft++;
    if(fireDecrementer.GetGlobalBounds().Contains(sf::Vector2f(x, y)) && firePoints > 1)
        firePoints--;
    else if(iceDecrementer.GetGlobalBounds().Contains(sf::Vector2f(x, y)) && icePoints > 1)
        icePoints--;
    else if(energyDecrementer.GetGlobalBounds().Contains(sf::Vector2f(x, y)) && energyPoints > 1)
        energyPoints--;
    else pointsLeft--;
}

void NewGameState::render()
{
    window->Draw(background);
    window->Draw(nameText);
    window->Draw(pointsLeftText);
    window->Draw(iceSkillText);
    window->Draw(fireSkillText);
    window->Draw(energySkillText);
    window->Draw(firePointsText);
    window->Draw(icePointsText);
    window->Draw(energyPointsText);
    window->Draw(fireIncrementer);
    window->Draw(fireDecrementer);
    window->Draw(iceIncrementer);
    window->Draw(iceDecrementer);
    window->Draw(energyIncrementer);
    window->Draw(energyDecrementer);

    startButton->draw(window);
    nameEdit->draw(window);
}

void NewGameState::init()
{
    pointsLeft = 5;
    firePoints = 1;
    icePoints = 1;
    energyPoints = 1;
}

void NewGameState::cleanup()
{
    std::ofstream file;
    file.open("Data/hero.txt");
    file << nameEdit->getText() << "\n";
    file << firePoints<< "\n";
    file << icePoints<< "\n";
    file << energyPoints<< "\n";
    file << 1 << "\n"; // level
    file << 0 << "\n"; // xp to next level
    file << 1 << "\n"; //amount of lives
    file << 100 << "\n"; //amount of mana
    file.close();
}
