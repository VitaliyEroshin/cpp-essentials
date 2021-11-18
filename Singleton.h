class Singleton {
  static Singleton* obj;
  Singleton() {};

public:
  static Singleton& getObject() {
    if(obj == nullptr)
      obj = new Singleton();
    
    return *obj;
  }

  static void destroy() {
    delete obj;
  }
};

Singleton* Singleton::obj = nullptr;

/*
  Only one singleton can exist at the same time.
  Every new singleton you create is the same object you created before.
*/