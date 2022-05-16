#ifndef _DEMO_HPP_
#define _DEMO_HPP_

#include <cstdlib>

#include "Video.hpp"
#include "LineMotion.hpp"
#include "TrigCache.hpp"

namespace g80 {
    class Demo : public Video {
    public:
        Demo();

        auto preprocess_states() -> bool;
        auto update_states() -> bool;

        /*
        virtual auto create_window(const VideoConfig &video_config) -> bool;
        virtual auto destroy_window() -> void;
        virtual auto preprocess_states() -> bool;
        virtual auto run() -> bool;
        virtual auto capture_events() -> bool;
        virtual auto update_states() -> bool;
        virtual auto update_window_surface() -> bool;
        */

    private:
        
        std::vector<LineMotion<float>> explosions_;
    };

    Demo::Demo() : Video() {

    }

    auto Demo::preprocess_states() -> bool {
        // line_motion_.line_motion_set({0.0f, 100.0f}, {1000.0f, 500.0f}, 50, 5);

        const Sint32 N = 360 * 20;
        SinCacheF sine(N);
        CosCacheF cosine(N);

        explosions_.reserve(N);
        for (int i = 0; i < N; ++i) {
            explosions_.emplace_back();
            explosions_[i].line_motion_set(
                {surface_->w / 2.0f, surface_->h / 2.0f},
                {surface_->w / 2.0f + cosine[i] * 700,
                surface_->h / 2.0f + sine[i] * 700}, 20 + rand() % 281, 1 + rand() % 5);
        } 

        return true;
    }

    auto Demo::update_states() -> bool {

        const Sint32 N = 360 * 20;
        SinCacheF sine(N);
        CosCacheF cosine(N);        
        Palette pal;
        pal.add_gradients(surface_->format, 40, 
            {
                {0, SDL_MapRGBA(surface_->format, 255, 255, 255, 255)},
                {60, SDL_MapRGBA(surface_->format, 255, 255, 0, 255)},
                {120, SDL_MapRGBA(surface_->format, 255, 100, 0, 255)},
                {180, SDL_MapRGBA(surface_->format, 255, 0, 0, 255)},
                {300, SDL_MapRGBA(surface_->format, 255, 0, 255, 255)},});
                

        // Erase
        SDL_FillRect(surface_, NULL, 0);
        
        // Draw
        // RGBAColor c = SDL_MapRGBA(surface_->format, 255, 255, 255, 255);
        for (auto &l : explosions_) {
            line(l.get_head(), l.get_tail(), pal[150.0f * l.get_tail_step() / l.get_size_of_step()]);
        }

        // Update
        for (int i = 0; i < N; ++i) {
            if (!explosions_[i].next()) 
                explosions_[i].line_motion_set(
                    {surface_->w / 2.0f, surface_->h / 2.0f},
                    {surface_->w / 2.0f + cosine[i] * 700,
                    surface_->h / 2.0f + sine[i] * 700}, 20 + rand() % 281, 1 + rand() % 5);
        } 

        // pset(line_motion_.get_tail(), SDL_MapRGBA(surface_->format, 255, 0, 0, 255));
        // pset(line_motion_.get_head(), SDL_MapRGBA(surface_->format, 255, 255, 255, 255));

        // line(line_motion_.get_head(), line_motion_.get_tail(), SDL_MapRGBA(surface_->format, 255, 255, 255, 255));

        // if (!line_motion_.next())
        //     exit(0);


        // Palette pal;
        // pal.add_gradients(surface_->format, 40, 
        //     {
        //         {0, SDL_MapRGBA(surface_->format, 255, 255, 255, 255)},
        //         {10, SDL_MapRGBA(surface_->format, 255, 255, 0, 255)},
        //         {20, SDL_MapRGBA(surface_->format, 255, 100, 0, 255)},
        //         {30, SDL_MapRGBA(surface_->format, 255, 0, 0, 255)},
        //         {40, SDL_MapRGBA(surface_->format, 255, 0, 255, 255)},});
        
        // // for (int i = 0; i < surface_->w - 1; ++i) {
        // //     int h =  100 + rand() % 500;
        // //     line_lite({i, surface_->h - 1}, {i, surface_->h - h}, pal, 0, 39);

        // // }
        
        // line({50, 700}, {300, 50}, SDL_MapRGBA(surface_->format, 255, 255, 255, 255));
        // line({300, 50}, {900, 300}, SDL_MapRGBA(surface_->format, 255, 255, 255, 255));
        // line({900, 300}, {700, 50}, SDL_MapRGBA(surface_->format, 255, 255, 255, 255));
        // line({700, 50}, {1000, 30}, SDL_MapRGBA(surface_->format, 255, 255, 255, 255));
        // line({1000, 30}, {1279, 700}, SDL_MapRGBA(surface_->format, 255, 255, 255, 255));

        // catmullrom_spline({{50, 700}, {300, 50}, {900, 300}, {700, 50}, {1000, 30}, {1279, 700}}, 100, pal, 0, 39);
        // catmullrom_spline_lite({{50, 700}, {300, 50}, {900, 300}, {700, 50}, {1000, 30}, {1279, 700}}, 50, SDL_MapRGBA(surface_->format, 255, 0, 0, 255));
        // exit(0);
        // quad_bezier_lite({50, 50}, {150,600}, {900,300}, 20, SDL_MapRGBA(surface_->format, 255, 255, 255, 255));
        // quad_bezier_lite({900, 300}, {1280, 700}, {50, 50}, 20, SDL_MapRGBA(surface_->format, 255, 255, 255, 255));

        // cubic_bezier_lite({50, 700}, {300, 0}, {900, 300}, {700, 50},  30, pal, 0, 39);
        // cubic_bezier_lite({700, 50}, {900, 100}, {700, 300}, {50, 700},  30, SDL_MapRGBA(surface_->format, 0, 255, 0, 255));
        // bezier_lite({{0, 100}, {200, 700}, {300, 0}, {400, 500}, {500,600}, {600, 50}, {1000,70}, {0, 100}},  100, pal, 0, 39);

        // line({-1000, surface_->h / 2}, {+3000, surface_->h / 2}, pal, 0, 39);
        // line({3000, surface_->h / 3}, {-1000, surface_->h / 3}, pal, 0, 39);
        //line({-1000, surface_->h / 2}, {+1000, surface_->h / 2}, SDL_MapRGBA(surface_->format, 255, 0, 0, 255));

        // quad_bezier_lite({50, 50}, {150,600}, {900,300}, 20, pal, 0, 39);

        return true;
    }
}

#endif 