/****************************************************/

class Crawler {
  public:
    Crawler();
    void begin();
    void go();
    void back();
    void rotate(int direction);
    void wait();

    void debug(char* message);

  private:
    int E1 = 10;
    int M1 = 12;
    int E2 = 11;
    int M2 = 13;

    int echoPin = 9;
    int trigPin = 8;
};
