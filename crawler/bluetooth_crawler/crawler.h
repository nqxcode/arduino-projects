/****************************************************/

class Crawler {
  public:
    Crawler(unsigned int e1, unsigned int m1, unsigned int e2, unsigned int m2);
    void begin();
    void go();
    void back();
    void rotate(int direction);
    void wait();

    void debug(char* message);

  private:
    int E1;
    int M1;
    int E2;
    int M2;
};
