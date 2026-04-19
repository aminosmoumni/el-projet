#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct {
    char name[20];
    int score;
} Score;


void saveScore(const char *name, int score) {
    FILE *f = fopen("scores.txt", "a");
    if (f) {
        fprintf(f, "%s %d\n", name, score);
        fclose(f);
    }
}

int loadScores(Score scores[]) {
    FILE *f = fopen("scores.txt", "r");
    int n = 0;
    if (f) {
        while (fscanf(f, "%19s %d", scores[n].name, &scores[n].score) != EOF && n < 10)
            n++;
        fclose(f);
    }
    return n;
}

void sortScores(Score scores[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (scores[j].score > scores[i].score) {
                Score tmp = scores[i];
                scores[i] = scores[j];
                scores[j] = tmp;
            }
}



void drawText(SDL_Renderer *r, TTF_Font *font, const char *txt, int x, int y) {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *s = TTF_RenderText_Solid(font, txt, white);
    if (!s) return;
    SDL_Texture *t = SDL_CreateTextureFromSurface(r, s);
    SDL_Rect pos = {x, y, s->w, s->h};
    SDL_RenderCopy(r, t, NULL, &pos);
    SDL_FreeSurface(s);
    SDL_DestroyTexture(t);
}



int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    SDL_Window *win = SDL_CreateWindow(
        "Sous Menu Meilleurs Scores",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, 0
    );

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture *bg = IMG_LoadTexture(ren, "background3.jpg");
    TTF_Font *font = TTF_OpenFont("arial.ttf", 24);
    Mix_Music *victory = Mix_LoadMUS("victory.mp3");

    SDL_Rect inputBox   = {250, 255, 300, 40};
    SDL_Rect btnValider = {350, 320, 120, 40};
    SDL_Rect btnRetour  = {500, 500, 120, 40};
    SDL_Rect btnQuitter = {650, 500, 120, 40};

    int running = 1;
    int showScores = 0;
    int score = 100;
    char playerName[20] = "";
    int len = 0;

    SDL_Event e;
    SDL_StartTextInput();

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = 0;

            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE)
                    running = 0;

                if (e.key.keysym.sym == SDLK_BACKSPACE && len > 0 && !showScores) {
                    playerName[--len] = '\0';
                }

                if (e.key.keysym.sym == SDLK_RETURN && !showScores) {
                    saveScore(playerName, score);
                    Mix_PlayMusic(victory, 0);
                    showScores = 1;
                }
            }

            if (e.type == SDL_TEXTINPUT && !showScores) {
                if (len < 19) {
                    strcat(playerName, e.text.text);
                    len++;
                }
            }
        }

        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, bg, NULL, NULL);

        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);

        if (!showScores) {
            drawText(ren, font, "Saisir Nom / Pseudo :", 260, 220);

            SDL_RenderDrawRect(ren, &inputBox);
            drawText(ren, font, playerName, inputBox.x + 10, inputBox.y + 5);

            SDL_RenderDrawRect(ren, &btnValider);
            drawText(ren, font, "Valider", btnValider.x + 25, btnValider.y + 5);

        } else {
            Score scores[10];
            int n = loadScores(scores);
            sortScores(scores, n);

            drawText(ren, font, "Meilleurs Scores", 300, 150);

            for (int i = 0; i < n && i < 3; i++) {
                char line[60];
                sprintf(line, "★ %s - %d", scores[i].name, scores[i].score);
                drawText(ren, font, line, 300, 230 + i * 50);
            }

            SDL_RenderDrawRect(ren, &btnRetour);
            SDL_RenderDrawRect(ren, &btnQuitter);

            drawText(ren, font, "Retour", btnRetour.x + 25, btnRetour.y + 5);
            drawText(ren, font, "Quitter", btnQuitter.x + 20, btnQuitter.y + 5);
        }

        SDL_RenderPresent(ren);
    }

    SDL_StopTextInput();
    Mix_FreeMusic(victory);
    SDL_DestroyTexture(bg);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);

    Mix_CloseAudio();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
