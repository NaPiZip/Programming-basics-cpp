// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE
class Game {
public:
  explicit Game(int number_of_players) : number_of_players_{ number_of_players } {}
  void run();
protected:
  virtual void start() = 0;
  virtual bool have_winner() = 0;
  virtual void take_turn() = 0;
  virtual int get_winner() = 0;

  int number_of_players_;
  int current_player_{ 0 };
};

class Chess : public Game {
public:
  explicit Chess() : Game{ 2 } {}

protected:
  void start() override {}
  bool have_winner() override { return turns_ == max_turns_; }
  void take_turn() override {
    turns_++;
    current_player_ = (current_player_ + 1) % number_of_players_;
  }
  int get_winner() override {
    return current_player_;
  }

private:
  int turns_{ 0 }, max_turns_{ 10 };
};
#endif // _HEADER_WORKSPACE
