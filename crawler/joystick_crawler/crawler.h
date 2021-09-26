/****************************************************/

class Crawler {
  public:
    enum class Direction
    {
      forward, backward, left_rotation, right_rotation
    };

    Crawler::Crawler(unsigned int e1, unsigned int m1, unsigned int e2, unsigned int m2, unsigned int buzzer);
    void begin();
    void debug(String message);

    void run(Direction direction);
    void speed(unsigned int leftSpeed, unsigned int rightSpeed);
    void buzz(void); 
    void enableDebugMode(void);

  private:
    unsigned int E1;
    unsigned int M1;
    unsigned int E2;
    unsigned int M2;
    unsigned int Buzzer;

    unsigned int leftSpeed;
    unsigned int rightSpeed;

    bool debugMode = false;

    void refreshSpeed(void);    
};
