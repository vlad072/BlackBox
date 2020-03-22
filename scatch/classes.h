class Input { //=============== input ===============
  public:
    Input(byte pin) {
      _pin = pin;
      pinMode(_pin, INPUT_PULLUP);
      _old = active();
    }
    bool active(void) {
      byte _cntr; do {
        _cntr = 0;
        for (byte _i = 0; _i < 10; _i++) _cntr += (byte)digitalRead(_pin);
      } while ((_cntr > 0) && (_cntr < 10));
      return !_cntr;
    }
    char change() {
      bool _state = active();
      if (_state == _old) return -1;
      _old = _state;
      return (char)_state;
    }
  private:
    byte _pin; bool _old;
};
class Adc { //================= adc =================
  public:
    Adc(byte pin, float k = 1, int ofs = 0) {
      _pin = pin; _ofs = ofs; _k = k;
      //pinMode(_pin, INPUT); // HI-Z default. wrong for A6, A7!!!
    }
    float value() {
      int  _readings[8] = {0,0,0,0,0,0,0,0};
      byte _ranges[8]   = {0,1,2,3,4,5,6,7};
      for (byte _readingnum = 0; _readingnum < 8; _readingnum++) {
        _readings[_readingnum] = analogRead(_pin);
        if (_readingnum)
          for (byte _prev = 0; _prev < _readingnum; _prev++)
            if (abs(_readings[_readingnum] - _readings[_prev]) < 5) {
              _ranges[_readingnum] = _ranges[_prev];
              break;
            }
      }
      byte _toprange = 0;
      byte _topcount = 0;
      for (byte _rangenum = 0; _rangenum < 8; _rangenum++) {
        byte _counter = 0;
        for (byte _readingnum = 0; _readingnum < 8; _readingnum++)
          if (_ranges[_readingnum] == _rangenum) _counter++;
        if (_counter > _topcount) _topcount = _counter, _toprange = _rangenum;
      }
      int  _average  = 0;
      for (byte _readingnum = 0; _readingnum < 8; _readingnum++)
        if (_ranges[_readingnum] == _toprange) _average += _readings[_readingnum];
      _average /= _topcount;
      return (_average - _ofs)/_k;
    }
    private:
    byte _pin; int _ofs; float _k;
};
class Output { //============== output ===============
  public:
    Output(byte pin) {
      _pin = pin;
      pinMode(_pin, OUTPUT); digitalWrite(_pin, LOW);
    }
    void set(bool val) {
      digitalWrite(_pin, val); _timeout = 0;
    }
    void run(uint32_t timeout) {
      digitalWrite(_pin, HIGH); _begin = millis(); _timeout = timeout;
    }
    bool on() {
      return digitalRead(_pin);
    }
    void processing() {
      if (!_timeout) return;
      if ((millis() - _begin) > _timeout) digitalWrite(_pin, LOW), _timeout = 0;        
    }
  private:
    byte _pin;
    uint32_t _begin   = 0;
    uint32_t _timeout = 0;
};
class InOut : public Input, Output { //====== in/out =======
  public:
    InOut(byte inpin, byte outpin) : Input(inpin), Output(outpin) { }
    bool set(bool val) {
      Output::set(val);
      return (active() == val);
    }
};
