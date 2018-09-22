/****************************************************/

class Crawler {
  public:
    enum class Direction
    {
      forward, backward, right, left
    };

    Crawler::Crawler(unsigned int e1, unsigned int m1, unsigned int e2, unsigned int m2, unsigned int _speed = 200);
    void begin();
    void debug(String message);

    void run(Direction direction);
    void stop();
    void speed(unsigned int _speed);

  private:
    unsigned int E1;
    unsigned int M1;
    unsigned int E2;
    unsigned int M2;
    unsigned int _speed;
};
