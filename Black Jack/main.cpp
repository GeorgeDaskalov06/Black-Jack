#include <iostream>
#include <vector>
#include <string>
#include <random>
using namespace std;
string club = "\5", diamond = "\4", hearts = "\3", spades = "\6";
int dealerPoints = 0, dealerPointsA = 0, playerPoints = 0, playerPointsA = 0, playerPoints2 = 0, playerPointsA2 = 0, choice = 0, p = 1;
int dealerScore = 0, playerScore = 0, playerScore2 = 0;
bool playerHasAce = false, playerHasAce2 = false, braked = true, splitted = false, dealerBusted = false, playerBusted = false, isBJ1 = false, isBJ2 = false;
int firstHand = 0, secondHand = 0, dealerHand = 0;
int money = 1000, bet = 0;
struct deck
{
    int points;
    string character;
};
vector<deck> Deck;
vector<deck> DealersHand;
vector<deck> PlayersHand;
vector<deck> PlayersHand2;
string suits[4] = {club, diamond, hearts, spades};
string ranks[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
void fillDeck()

{
    for (int s = 0; s < 4; s++)
    {
        for (int r = 0; r < 13; r++)
        {
            deck card;
            card.character = ranks[r] + suits[s];
            if (r > 8 && r < 12)
            {
                card.points = 10;
            }
            else if (r == 12)
            {
                card.points = 11;
            }
            else
            {
                card.points = r + 2;
            }
            Deck.push_back(card);


        }
    }
}
int takeIndex ()
{
    int index;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(0, (Deck.size() - 1));
    index = distribution(gen);
    return index;
}
void takeCard(char pod)
{
    switch(pod)
    {
        case 'p':
        {
            int takenCard = takeIndex();
            deck playersCard;
            playersCard.character = Deck[takenCard].character;
            playersCard.points = Deck[takenCard].points;
            PlayersHand.push_back(playersCard);
            Deck.erase(Deck.begin() + takenCard);
            break;
        }
        case 'd':
        {
            int takenCard = takeIndex();
            deck dealersCard;
            dealersCard.character = Deck[takenCard].character;
            dealersCard.points = Deck[takenCard].points;
            DealersHand.push_back(dealersCard);
            Deck.erase(Deck.begin() + takenCard);
            break;
        }
        case '2':
            int takenCard = takeIndex();
            deck playersCard2;
            playersCard2.character = Deck[takenCard].character;
            playersCard2.points = Deck[takenCard].points;
            PlayersHand2.push_back(playersCard2);
            Deck.erase(Deck.begin() + takenCard);
            break;
    }
}
void printCard(char pod,bool hasSign, int number)
{
    string sign;
    if (pod == 'p')
    {
        sign = PlayersHand[number].character;
        playerPoints += PlayersHand[number].points;
        if (sign[0] == 'A') {playerPointsA += 1; playerHasAce = true;}
        else {playerPointsA += PlayersHand[number].points;}
    }
    else if (pod == 'd')
    {
        sign = DealersHand[number].character;
        dealerPoints += DealersHand[number].points;
        if (sign[0] == 'A') {dealerPointsA += 1;}
        else {dealerPointsA += DealersHand[number].points;}
    }
    else
    {
        sign = PlayersHand2[number].character;
        playerPoints2 += PlayersHand2[number].points;
        if (sign[0] == 'A') {playerPointsA2 += 1; playerHasAce2 = true;}
        else {playerPointsA2 += PlayersHand2[number].points;}
    }
    char firstCharacter = sign[0];
    bool isTen = false;
    if (firstCharacter == '1') {isTen = true;}
    switch (isTen)
    {
        case true:
        {
            if (hasSign)
            {
                cout << ".________." << endl;
                cout << "|" << sign << "     |" << endl;
                cout << "|        |" << endl;
                cout << "|        |" << endl;
                cout << "|     "<< sign << "|" << endl;
                cout << "|________|" << endl;
            }
            else
            {
                cout << ".________." << endl;
                cout << "|        |" << endl;
                cout << "|        |" << endl;
                cout << "|        |" << endl;
                cout << "|        |" << endl;
                cout << "|________|" << endl;
            }
            break;
        }
        default:
        {
            if (hasSign)
            {
                cout << ".________." << endl;
                cout << "|" << sign << "      |" << endl;
                cout << "|        |" << endl;
                cout << "|        |" << endl;
                cout << "|      "<< sign << "|" << endl;
                cout << "|________|" << endl;
            }
            else
            {
                cout << ".________." << endl;
                cout << "|        |" << endl;
                cout << "|        |" << endl;
                cout << "|        |" << endl;
                cout << "|        |" << endl;
                cout << "|________|" << endl;
            }
            break;
        }
    }
}
void Card(char pod, int number)
{
    takeCard(pod);
    switch(pod) {
        case 'p':
        {
            printCard(pod, true, number);
            break;
        }
        case 'd':
        {
            printCard(pod, p, number);
            break;
        }
        case '2':
        {
            printCard('2', true, number);
            break;
        }
        default:
            break;
    }
}
void betting()
{
    cin >> bet;
    if (bet < 20 || bet > money)
    {
        cout << "You can`t bet this amount of money!" << endl;
        cout << "Try again: " << endl;
    }
}
void renew()
{
    Deck.clear();
    DealersHand.clear();
    PlayersHand.clear();
    PlayersHand2.clear();
    dealerPoints = 0, dealerPointsA = 0, playerPoints = 0, playerPointsA = 0, playerPoints2 = 0, playerPointsA2 = 0, choice = 0, p = 1;
    dealerScore = 0, playerScore = 0, playerScore2 = 0;
    playerHasAce = false, playerHasAce2 = false, braked = true, splitted = false, dealerBusted = false, playerBusted = false, isBJ1 = false, isBJ2 = false;
    firstHand = 0, secondHand = 0, dealerHand = 0;
}
void endGame(int player_score)
{
        if (player_score > dealerScore) {
            cout << "You win the round!" << endl;
            money += bet;
        } else if (player_score < dealerScore) {
            cout << "The Dealer wins the round!" << endl;
            money -= bet;
        } else {
            cout << "It's a push (tie), you get your bet back." << endl;
        }
}
int main() {
    cout << "!Welcome to the BlackJack table!" << endl;
    while (true) {
        cout << "You have " << money << " BGN" << endl;
        cout << "Enter your bet from (" << "20 / " << money << "):" << endl;
        do {
            betting();
        } while (bet < 20 || bet > money);
        fillDeck();
        for (int i = 0; i < 4; i++) {
            switch (i) {
                case 0:
                case 1: {
                    takeCard('p');
                    break;
                }
                case 2:
                case 3: {
                    takeCard('d');
                    break;
                }
            }
        }
        p = 1;
        cout << "Dealers Hand:" << endl;
        Card('d', dealerHand);
        p--;
        dealerHand++;
        Card('d', dealerHand);
        cout << endl;
        cout << "Your Hand:" << endl;
        p = 1;
        Card('p', firstHand);
        firstHand++;
        Card('p', firstHand);
        firstHand = 2;
        dealerHand = 2;
        bool split = false;
        int firstCard = PlayersHand[0].points, secondCard = PlayersHand[1].points;
        if (firstCard == secondCard) {
            split = true;
        }
        if (playerPoints == playerPointsA) {
            cout << "Your points are: " << playerPoints << endl;
        } else if (playerPoints == 21) {
            cout << "!!!BLACKJACK!!!" << endl;
            isBJ1 = true;
        } else {
            cout << "Your points are: " << playerPointsA << " / " << playerPoints << endl;
        }
        if (isBJ1) {
            cout << "You won with BlackJack!" << endl;
        } else {
            while (choice != 2 && (playerPoints <= 21 || playerPointsA <= 21) && braked && !isBJ1) {
                cout << "1. Hit" << endl;
                cout << "2. Stand" << endl;
                if (split) {
                    cout << "3. Split" << endl;
                    split = false;
                }
                cin >> choice;
                switch (choice) {
                    case 1: {
                        Card('p', firstHand);
                        firstHand++;
                        if (playerPoints <= 21) {
                            cout << "Your points are: " << playerPoints << endl;
                        } else if (playerHasAce && playerPointsA <= 21) {
                            cout << "Your points are: " << playerPointsA << endl;
                        } else {
                            cout << "!BUSTED!" << endl;
                            cout << "You lost your bet" << endl;
                            money -= bet;
                            playerBusted = true;
                        }
                        split = false;
                        break;
                    }
                    case 2:
                        break;
                    case 3: {
                        choice = 0;
                        playerPoints = 0;
                        playerPointsA = 0;
                        firstHand = 0;
                        splitted = true;
                        playerScore = PlayersHand[0].points, playerScore2 = PlayersHand[1].points;
                        deck card = {PlayersHand[1].points, PlayersHand[1].character};
                        PlayersHand2.push_back(card);
                        PlayersHand.erase(PlayersHand.begin() + 1);
                        cout << "First Hand:" << endl;
                        printCard('p', true, firstHand);
                        firstHand++;
                        Card('p', firstHand);
                        firstHand++;
                        if (playerPoints == playerPointsA) {
                            cout << "Your points are: " << playerPoints << endl;
                        } else if (playerPoints == 21) {
                            cout << "!!!BLACKJACK!!!" << endl;
                            isBJ1 = true;
                        } else {
                            cout << "Your points are: " << playerPointsA << " / " << playerPoints << endl;
                        }
                        if (isBJ1) {
                            cout << "You won with BlackJack!" << endl;
                        }
                        while (choice != 2 && (playerPoints < 21 || playerPointsA < 21)) {
                            cout << "1. Hit" << endl;
                            cout << "2. Stand" << endl;
                            cin >> choice;
                            switch (choice) {
                                case 1: {
                                    Card('p', firstHand);
                                    firstHand++;
                                    if (playerPoints <= 21) {
                                        cout << "Your points are: " << playerPoints << endl;
                                    } else if (playerHasAce && playerPointsA <= 21) {
                                        cout << "Your points are: " << playerPointsA << endl;
                                    } else {
                                        cout << "!BUSTED!" << endl;
                                        cout << "You lost your bet" << endl;
                                    }
                                    break;
                                }
                                case 2:
                                    break;
                                default:
                                    break;
                            }
                        }
                        cout << "Second Hand: " << endl;
                        choice = 0;
                        secondHand = 0;
                        printCard('2', true, secondHand);
                        secondHand++;
                        Card('2', secondHand);
                        secondHand++;
                        if (playerPoints2 == playerPointsA2) {
                            cout << "Your points are: " << playerPoints2 << endl;
                        } else if (playerPoints2 == 21) {
                            cout << "!!!BLACKJACK!!!" << endl;
                            isBJ2 = true;
                        } else {
                            cout << "Your points are: " << playerPointsA2 << " / " << playerPoints2 << endl;
                        }
                        if (isBJ1) {
                            cout << "You won with BlackJack!" << endl;
                        }
                        while (braked && choice != 2 && (playerPoints2 < 21 || playerPointsA2 < 21)) {
                            cout << "1. Hit" << endl;
                            cout << "2. Stand" << endl;
                            cin >> choice;
                            switch (choice) {
                                case 1: {
                                    Card('2', secondHand);
                                    secondHand++;
                                    if (playerPoints2 <= 21) {
                                        cout << "Your points are: " << playerPoints2 << endl;
                                    } else if (playerHasAce2 && playerPointsA2 <= 21) {
                                        cout << "Your points are: " << playerPointsA2 << endl;
                                    } else {
                                        cout << "!BUSTED!" << endl;
                                        cout << "You lost your bet" << endl;
                                        money -= bet;
                                        braked = false;
                                    }
                                    break;
                                }
                                default:
                                    break;
                            }
                        }
                    }
                }
            }
        }
        if (playerPoints <= 21) {
            playerScore = playerPoints;
        } else {
            playerScore = playerPointsA;
        }
        if (splitted) {
            if (playerPoints2 <= 21) {
                playerScore2 = playerPoints2;
            } else {
                playerScore2 = playerPointsA2;
            }
        }
        choice = 0;
        dealerPoints = 0;
        dealerPointsA = 0;
        cout << "Dealers Hand: " << endl;
        printCard('d', true, 0);
        printCard('d', true, 1);
        if (dealerPoints <= 21) {
            dealerScore = dealerPoints;
        }
        else {
            dealerScore = dealerPointsA;
        }
        if (isBJ1 && !splitted)
        {
            cout << "You win the round with BlackJack!" << endl;
            money += bet + (bet / 2);
        }
        if (!playerBusted) {
            while (dealerScore < 17 && !isBJ1) {
                Card('d', dealerHand);
                dealerHand++;
                if (dealerPoints <= 21) {
                    dealerScore = dealerPoints;
                } else {
                    dealerScore = dealerPointsA;
                }
                if (dealerScore > 21) {
                    cout << "The Dealer BUSTED" << endl;
                    cout << "You win the round!" << endl;
                    money += bet;
                    dealerBusted = true;
                    break;
                }
            }
            if (!splitted && !dealerBusted) {
                cout << "Your final points: " << playerScore << endl;
                cout << "Dealer's final points: " << dealerScore << endl;
                endGame(playerScore);
            }
            else if (playerBusted) {
                money -= bet;
            }
            else if (splitted && !dealerBusted) {
                bet *= 2;
                cout << "First Hand: " << endl;
                endGame(playerScore);
                cout << "Second Hand: " << endl;
                endGame(playerScore2);
            }
        }
        renew();
    }
}