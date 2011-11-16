typedef struct {
    float x;
    float y;
    float z;
}punto;

typedef struct{
    float shot_v;
    float trayec_v;
    punto *points;

    oponentes(int A):points(new float[A]){}
    ~oponentes(){delete[] points;}
}oponentes;

typedef struct{
    punto v;
    int rebotes;
    punto pos;
}disco;

typedef struct {
    int level_id;
    int game_time;
    float player_shot_v;
    float trayec_v;
    puntos *points;
    oponentes opo[3];
}nivel;
