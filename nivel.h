#include <vector>

typedef struct {
    float x;
    float y;
    float z;
}punto;

typedef struct jugadores{
    float shot_v;
    float trayec_v;
    int nro_puntos;
    punto points[100];

    public:
    jugadores(){};
    jugadores(int A):nro_puntos(A){}
    jugadores(jugadores &A){
        shot_v = A.shot_v;
        trayec_v = A.trayec_v;
        nro_puntos = A.nro_puntos;
        memcpy(points,A.points,sizeof(punto)*A.nro_puntos);
     }
}jugadores;

typedef struct{
    punto v;
    int rebotes;
    punto pos;
}disco;

typedef struct obstaculos{
    int tipo;
   //Trimesh mesh;
    punto points;
}obstaculos;

typedef struct nivel{
    int level_id;
    int game_time;
    jugadores player[4];
    std::vector<obstaculos> objs ;  
   
    public:
    nivel(const nivel &A){
        level_id = A.level_id;
        game_time = A.game_time;
        memcpy(player, A.player, sizeof(jugadores)*4);
        objs = A.objs ;
    }
    nivel(){}
    
}nivel;
