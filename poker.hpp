#ifndef __POKER_HPP
#define __POKER_HPP

#define TABLE_MAX 5
#define DECK_MAX 52
#define DECK_MAX_JOKERS 54

#include <vector>


class Card {
    public:
        void setSuit(const std::string &suit);
        std::string getSuit() const;
    
        void setRank(const std::string &rank);
        std::string getRank() const;
    
    private:
        std::string suit, rank;
};

class Player {
    private:
        int balance,
            numCards;
            
        bool isTurn;
};

class Poker {
    public:
        // DECK FUNCTIONS
        // --------------------
        void shuffleDeck();
        void dealDeck();
        int deckSize() const;
        bool isDeckEmpty() const;
        const Card &deckTop() const;
        Card &drawTop();
        void insertDeckBottom();
        
        // PLAYER FUNCTIONS
        void playerCheck();
        void playerFold(Player &player);
        void playerBet(Player &player, int bet)
        void playerCall(Player &player, int );
        void playerRaise(Player);
        
        void playerInfo(Player &player);
        void allPlayerInfo();
        
        
    private:
        const std::string suits[4] = {"spades", "hearts", "diamonds", "clubs"};
            // id = i + 1
        const std::string ranks[13] = {
                "ace",
                "two",
                "three",
                "four",
                "five",
                "six",
                "seven",
                "eight",
                "nine",
                "ten",
                "jack",
                "queen",
                "king"
        };
        const std::string hands[10] = {
            "high card",
            "pair",
            "two pair",
            "three of a kind",
            "straight",
            "flush",
            "full house",
            "four of a kind",
            "straight flush",
            "royal flush"
        };
        
        std::vector<Player> m_Players;
        std::vector<Card> m_Table;
        std::vector<Card> m_Deck;
        
        // PLAYER VARIABLES
        Player &m_Turn;
};

#endif // __POKER_HPP