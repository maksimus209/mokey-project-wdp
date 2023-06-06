#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
using namespace sf;

/*struktura polozenie platform na planszy gry
x wspolrzedna pozioma
y wpolrzedna pionowa
*/
struct point
{
    int x, y;
};

int main()
{
    //generowanie pseudolosowych liczb
    srand(time(0));


    //rozmiary plaszczyzny gry; 400 - szerokosc, 533 - wysokosc
    const int SCREEN_WIDTH = 400;
    const int SCREEN_HEIGHT = 533;

    //okno renderowania o okreslonym rozmiarze na podstawie width i height w pikselach
    RenderWindow app(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Monkey Jump");
    //limit klatek na 60 klatek na sekunde dla okna renderowania
    app.setFramerateLimit(60);

    /* 
    tworzenie struktur dla obiketow w grze oraz ladowanie ich zdjec
    */
    Texture t1, t2, t3, t4;
    t1.loadFromFile("background.png");
    t2.loadFromFile("platform.png");
    t3.loadFromFile("doodle.png");
    t4.loadFromFile("monster.png");

    //tworzenie obiektow reprezentowanych na podstawie stworzonych struktur
    Sprite sBackground(t1), sPlat(t2), sPers(t3), sObject(t4);

    /*
    polozenie wspolrzednych platform w grze. 
    element tablicy plat - jedna platforma (wspolrzedne x i y)
    */
    point plat[20];

    //generowanie pierwszych dzisieciu platform w sposob losowy
    //na ekranie 10 platform
    for (int i = 0; i < 10; i++)
    {
        //czestliwosc pojawiania sie platform poziomowo i pionowo
        plat[i].x = 200 + rand() % SCREEN_WIDTH;
        plat[i].y = 100 + rand() % SCREEN_HEIGHT;
    }

    //polozenie i wysokosc obiektu w grze
    int x = 200, y = 200, h = 200;
    //predkosc obiektu w osiach x i y
    float dx = 0, dy = 0;
    //aktualny wynik gracza w grze
    int score = 0;
    //najlepszy wynik
    int bestScore = 0;
    //czy gra zostala zakonczona
    bool gameOver = false;
    //czy zostal klikniety przycisk restartu
    bool restartClicked = false;
    //czy zostal ustaowiony nowy rekord
    bool newRecord = false;
    //czy gra zostala uruchomiona
    bool gameStarted = false;
    //wyswietlanie menu grzy
    bool menu = true;
    //aktywnosc obiektu w graze
    bool objectActive = false;
    //sledzenie czasu w grze
    int objectTimer = 0;
    //maksymalny czas dla niektorych funkcjonalnosci w grze
    int objectTimerMax = 30;

    //podlaczenie czcionki
    Font font;
    font.loadFromFile("Super Bubble.ttf");

    //text Score w lewym gornym kacie
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(35);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(10, 10);

    //text Restart po zakonczeniu gry
    Text restartText;
    restartText.setFont(font);
    restartText.setCharacterSize(40);
    restartText.setFillColor(Color::Red);
    restartText.setString("Restart");

    //przycisk ktory zawiera text restart i uruchamia gre ponownie z zresetowanymi danymi
    RectangleShape restartButton(Vector2f(250, 100));
    restartButton.setFillColor(Color(100, 100, 100, 200));

    //Tytul gry w menu startowym
    Text gameTitle;
    gameTitle.setFont(font);
    gameTitle.setCharacterSize(45);
    gameTitle.setFillColor(Color(255, 98, 0));
    gameTitle.setString("Monkey Jump");
    //pozycja polowa szerokosci i 200 px od gornej krawedzi
    gameTitle.setPosition(SCREEN_WIDTH / 2 - gameTitle.getGlobalBounds().width / 2, 200);
    
    //tytul najlepszego wyniku
    Text bestScoreText;
    bestScoreText.setFont(font);
    bestScoreText.setCharacterSize(28);
    bestScoreText.setFillColor(Color::Red);
    //pozycja polowa zerokosci i nad przyciskiem restartu
    bestScoreText.setPosition(SCREEN_WIDTH / 2 - bestScoreText.getGlobalBounds().width / 2, restartButton.getPosition().y + 2);

    //text new record
    Text newRecordText;
    newRecordText.setFont(font);
    newRecordText.setCharacterSize(40);
    newRecordText.setFillColor(Color::Red);
    newRecordText.setString("Record");
    //pozycja polowa szerokosci i nad najlepszym wynikiem
    newRecordText.setPosition(SCREEN_WIDTH / 2 - newRecordText.getGlobalBounds().width / 2, bestScoreText.getPosition().y - 120);


    // Ustawienie pozycji monstru poza granicami planszy w gorze
    sObject.setPosition(-100, -100);

    //przycisk start
    RectangleShape startButton(Vector2f(200, 80));
    startButton.setFillColor(Color(100, 100, 100, 200));
    startButton.setPosition(SCREEN_WIDTH / 2 - startButton.getSize().x / 2, SCREEN_HEIGHT / 2);

    //text start
    Text startButtonText;
    startButtonText.setFont(font);
    startButtonText.setCharacterSize(35);
    startButtonText.setFillColor(Color(255, 98, 0));
    startButtonText.setString("Start");
    //polozenie tekstu i przycisku
    startButtonText.setPosition(startButton.getPosition().x + startButton.getSize().x / 2 - startButtonText.getGlobalBounds().width / 2,
    startButton.getPosition().y + startButton.getSize().y / 2 - startButtonText.getGlobalBounds().height / 2);

    //czy glowne okno aplikacji jest otwarte
    while (app.isOpen())
    {
        //aktualna pozycja myszki w pikselach na ekranie
        Vector2f mousePosition = static_cast<Vector2f>(Mouse::getPosition(app));
        //mozliowsc interakcji myszki z obiektami w oknie gry
        Vector2f scaledMousePosition = Vector2f(
            mousePosition.x * static_cast<float>(SCREEN_WIDTH) / app.getSize().x,
            mousePosition.y * static_cast<float>(SCREEN_HEIGHT) / app.getSize().y);
        
        //przechowywania informacji o zdarzeniach w grze
        Event e;
        while (app.pollEvent(e))
        {
            //zamykanie okna aplikacji
            if (e.type == Event::Closed)
                app.close();
            //gra w trakcie
            else if (e.type == Event::MouseButtonPressed)
            {
                //menu startowe
                if (menu)
                {
                    //uruchomienie gry poprzez przycisniecie start
                    if (startButton.getGlobalBounds().contains(scaledMousePosition))
                    {
                        //zamykanie menu
                        menu = false;
                        //start gry
                        gameStarted = true;
                    }
                }
                //poczatek gry
                else if (gameStarted)
                {
                    //dzialanie restart
                    if (e.mouseButton.button == Mouse::Left)
                    {
                        //restart
                        if (restartButton.getGlobalBounds().contains(scaledMousePosition))
                        {
                            //pocztek gry od nowa
                            if (gameOver)
                            {
                                gameOver = false;
                                restartClicked = true;
                            }
                        }
                    }
                }
            }
        }

        //gra w trakcie
        if (gameStarted)
        {
            if (!gameOver)
            {
                //poruszanie sie w prawo i w lewo
                if (Keyboard::isKeyPressed(Keyboard::Right))
                    x += 3;
                if (Keyboard::isKeyPressed(Keyboard::Left))
                    x -= 3;

                //przesuwanie sie obiektu w zaleznosci od przekroczonej granicy
                //jezeli prawa - pozycja lewa
                if (x > SCREEN_WIDTH)
                    x = -50;
                //jezeli lewa - pozycja prawa
                else if (x < -50)
                    x = SCREEN_WIDTH;

                //predkosc w pionowym kierunku pezyspiesza sie w gore
                dy += 0.2;
                //przemieszczenie sie obiketu w dol
                y += dy;

                //koniec gry jezeli odbywa sie przekroczenie dolnej granicy
                if (y > SCREEN_HEIGHT)
                    gameOver = true;

                //znajdownaia sie obiektu powyzej platformy
                if (y < h)
                {
                    //10 platform na okienku gry
                    for (int i = 0; i < 10; i++)
                    {
                        //ustawienie pozycji obiektu na wysokosci platformy
                        y = h;
                        //przesuniecie plaformy w w gore wraz z ruchem obiektu
                        plat[i].y = plat[i].y - dy;

                        //platforma znajduje sie ponizej ekranu
                        if (plat[i].y > SCREEN_HEIGHT)
                        {
                            //nowe platformy w gorze losowo
                            plat[i].y = 0;
                            plat[i].x = rand() % SCREEN_WIDTH;
                        }
                    }
                }

                //sprawdzanie kolizji obiektu z platformami
                for (int i = 0; i < 10; i++)
                {
                    //w zaleznosci od pozycji malpy wobec platformy kolizja z nia
                    if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68) &&
                        (y + 75 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0))
                    {
                        //czy obiekt powyzej platformy
                        if (y < plat[i].y)
                        {
                            //odbylo sie zderzenie 
                            bool alreadyHit = false;
                            //sprawdzenie pozycji innych platform
                            for (int j = 0; j < 10; j++)
                            {
                                //czy ktoras jest ponizej uderzonej
                                if (plat[j].y != -1000 && j != i && plat[j].y < y)
                                {
                                    alreadyHit = true;
                                    break;
                                }
                            }

                            //zwiekdzenie wyniku oraz znikanie ponizszych platform
                            if (!alreadyHit)
                            {
                                score++;
                                plat[i].y = -1000;
                            }
                        }
                        // Dodajemy inkrementację score
                        score++;
                        //skok obiektu w gore po zdarzeniu
                        dy = -10;
                    }
                }
                //trafienie na monstra z gory
                if (objectActive && sPers.getGlobalBounds().intersects(sObject.getGlobalBounds()))
                {
                    // czy monkey porusza sie w dol
                    if (dy > 0) 
                    {
                        // Ustawiamy skok monkey w gore
                        dy = -10; 
                        // dodajemy 5 punktow do score w przypdaku uderzenia w monstra z gory
                        score += 5; 
                        //znikanie obiektu monster po zderzeniu
                        objectActive = false; 
                        //obiekt monster w nowej pozycji za planszą
                        sObject.setPosition(-100, -100); 
                    }

                    //trafienie na monstra w innych miejscach ale nie z gory co powoduje koniec gry
                    else
                    {
                        gameOver = true; 
                    }
                }

                sPers.setPosition(x, y);
            }

            // Logika pojawiania się obiektu
            if (!objectActive && !gameOver && !restartClicked && score > 5)
            {
                //pojawienie sie obiektow z pewna czestliowascia
                if (objectTimer >= objectTimerMax)
                {
                    //resetowanie czasu i wlaczenie aktywnosci obiektu
                    objectTimer = 0;
                    objectActive = true;
                    //losowa wartosc pojawienia sie weza
                    sObject.setPosition(rand() % SCREEN_WIDTH, -100);
                }
                //nie uplynecie potrzebnej ilosci czasu
                else
                {
                    objectTimer++;
                }
            }

            //przesuwanie weza w dol planszy
            if (objectActive && sObject.getPosition().y < SCREEN_HEIGHT)
            {
                //predkosc przesuwania sie
                sObject.move(0, 2);
            }

            //resetowanie pozycji weza 
            else if (objectActive && sObject.getPosition().y >= SCREEN_HEIGHT)
            {
                //dawanie pozycji weza ponownie w gorze
                objectActive = false;
                sObject.setPosition(-100, -100);
            }

            //sprawdzanie pozycji gracza wobec platformy na ktora mozna podskoczyc
            if (y < h)
                //aktualizacja pozycji platformy
                for (int i = 0; i < 10; i++)
                {
                    //pozycja graca na pozycji platformy
                    y = h;
                    //pozycja platformy staje sie predkoscia przesuwania graczy w pionie
                    plat[i].y = plat[i].y - dy;

                    //nowe platformy losowe
                    if (plat[i].y > SCREEN_HEIGHT)
                    {
                        plat[i].y = 0;
                        plat[i].x = rand() % SCREEN_WIDTH;
                    }
                }
        }

        //jesli nastapil restart gry - poczatkowe wartosci
        if (restartClicked)
        {
            //ustalanie nowego wyniku
            if (score > bestScore)
            {
                bestScore = score;
                //pojawienie sie tekstu nowego recordu
                newRecord = true;
            }
            //resetowanie wyniku gry
            score = 0;
            //poczatek gry ponownie
            gameOver = false;
            //zniaknie restartu po kliknieciu
            restartClicked = false;
            //pozycja gracza
            x = 100;
            y = 200;
            dy = 0;
            //pojawianie sie platform od zera
            for (int i = 0; i < 10; i++)
            {
                plat[i].x = rand() % SCREEN_WIDTH;
                plat[i].y = rand() % SCREEN_HEIGHT;
            }
        }
        //nowe rysowanie elementow
        app.clear();
        //ustalanie tla
        app.draw(sBackground);
        
        //elementy w menu startowym
        if (menu)
        {
            app.draw(gameTitle);
            app.draw(startButton);
            app.draw(startButtonText);
        }

        //gra uruchomiona
        else if (gameStarted)
        {
            //rywoanie 10 platform
            for (int i = 0; i < 10; i++)
            {
                sPlat.setPosition(plat[i].x, plat[i].y);
                app.draw(sPlat);
            }

            //pojawianie sie weza
            if (objectActive)
                app.draw(sObject);

            //obiekt ktorym gra gracz
            app.draw(sPers);

            //zapisywanie tekstu wyniku
            scoreText.setString("Score: " + std::to_string(score));
            app.draw(scoreText);

            //koniec gry jako pierwsza runda
            if (gameOver)
            {
                //ustalanie najlepszego wyniku
                if (score > bestScore)
                {
                    bestScore = score;
                    newRecord = true;
                }

                //pozycja przycisku restart
                restartButton.setPosition(SCREEN_WIDTH / 2 - restartButton.getSize().x / 2, SCREEN_HEIGHT / 2);
                
                //przycisk restartu
                app.draw(restartButton);

                //tekst w przycisku
                restartText.setPosition(restartButton.getPosition().x + restartButton.getSize().x / 2 - restartText.getGlobalBounds().width / 2,
                    restartButton.getPosition().y + restartButton.getSize().y / 2 - restartText.getGlobalBounds().height / 2);
                app.draw(restartText);

                //tekst i pozycja najlepszego wyniku
                bestScoreText.setString("Best Score: " + std::to_string(bestScore));
                bestScoreText.setPosition(SCREEN_WIDTH / 2 - bestScoreText.getGlobalBounds().width / 2, restartButton.getPosition().y - 30);
                app.draw(bestScoreText);

                //pozycja pojawiania sie nowego rekordu
                if (newRecord)
                {
                    newRecordText.setPosition(SCREEN_WIDTH / 2 - newRecordText.getGlobalBounds().width / 2, bestScoreText.getPosition().y - 40);
                    app.draw(newRecordText);
                }
            }
        }

        app.display();
    }

    return 0;
}