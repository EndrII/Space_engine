#include "EMapCore.h"
EMapCore::EMapCore():
    EThreadObject()
{
   cliced=full=false;
   priority_=LOW_PLUS;
   puls=true;
   buffer_for_draw=new EObject_List;
   buffer_for_render=new EObject_List;
   buffer_for_Game=new EObject_List;
}
void EMapCore::update(EObject_List *object_list,
                         EObject_List **slow_render_list,
                         EObject_List **render_list,
                         EObject_List **draw_list,
                         EObject_List **GameObjectList,
                         Elist<EKord*> *k)
{
    camers=k;
    object_list_=object_list;
    slow_render_list_=slow_render_list;
    render_list_=render_list;
    Game_List=GameObjectList;
    draw_list_=draw_list;
    full=true;
    cliced=false;
}
void EMapCore::click(EMouseEvent *event){
    clicedevent=event;
    cliced=true;
}
void EMapCore::render()
{
    while(puls&&full)
    {
        BaseRender();
        (*draw_list_)->Elock();
        pointer_void=*draw_list_;
        *draw_list_=buffer_for_draw;
        buffer_for_draw=(EObject_List*)(pointer_void);
        buffer_for_draw->Eun_lock();
        (*draw_list_)->Eun_lock();
        buffer_for_draw->clear();

        (*render_list_)->Elock();
        pointer_void=*render_list_;
        *render_list_=buffer_for_render;
        buffer_for_render=(EObject_List*)(pointer_void);
        buffer_for_render->Eun_lock();
        (*render_list_)->Eun_lock();
        buffer_for_render->clear();

        (*Game_List)->Elock();
        pointer_void=*Game_List;
        *Game_List=buffer_for_Game;
        buffer_for_Game=(EObject_List*)(pointer_void);
        buffer_for_Game->Eun_lock();
        (*Game_List)->Eun_lock();
        buffer_for_Game->clear();
        std::this_thread::sleep_for(std::chrono::milliseconds(priority_));
    }
}
void EMapCore::BaseRender(){
    (*slow_render_list_)->Eclear();
    for(Elist<EObject*>::iterator  i=object_list_->begin();i!=object_list_->end();i++)
    {
        //bool b=(*i)->delete_flag;
        if((*i)->delete_flag)
        {
            object_list_->erase(i);
            i--;
            if(object_list_->size()==0)
                return;
        }else
        {
            if((*i)->getEObjectNameClass()==E_GAMEOBJECT){
                buffer_for_Game->Epush_back(*i);
                if(cliced&&(*i)->getContur()->touching(clicedevent->x,clicedevent->y)){
                    (*i)->click(clicedevent->button);
                }
            }
            draw_=0;
            for(EKord* j:*camers)
               draw_+=(!(*i)->noDraw_flag&&(*i)->getKord().inQuan(j[0]-(*i)->getSize(),j[1]+(*i)->getSize()));
            if(draw_>0)
            {
                if(!(*i)->noDraw_flag)
                    buffer_for_draw->push_back(*i);
                if(!(*i)->ignore_flag)
                {
                    buffer_for_render->push_back(*i);
                    (*i)->setFeedBack(inFastRender);
                }
            }else
            {
                 if((*i)->forceRenderFlag)
                 {
                      buffer_for_render->push_back(*i);
                     (*i)->setFeedBack(inFastRender);
                 }
                 else
                 { 
                     (*slow_render_list_)->push_back(*i);
                     (*i)->setFeedBack(inSlowRender);
                 }
            }
        }
    }
    if(cliced)
        cliced=false;
}
void EMapCore::ForseRender()
{
    if(full){
        BaseRender();
        (*draw_list_)->Elock();
        pointer_void=*draw_list_;
        *draw_list_=buffer_for_draw;
        buffer_for_draw=(EObject_List*)(pointer_void);
        buffer_for_draw->Eun_lock();
        (*draw_list_)->Eun_lock();
        buffer_for_draw->clear();

        (*render_list_)->Elock();
        pointer_void=*render_list_;
        *render_list_=buffer_for_render;
        buffer_for_render=(EObject_List*)(pointer_void);
        buffer_for_render->Eun_lock();
        (*render_list_)->Eun_lock();
        buffer_for_render->clear();

        (*Game_List)->Elock();
        pointer_void=*Game_List;
        *Game_List=buffer_for_Game;
        buffer_for_Game=(EObject_List*)(pointer_void);
        buffer_for_Game->Eun_lock();
        (*Game_List)->Eun_lock();
        buffer_for_Game->clear();
    }
}
EMapCore::~EMapCore()
{
    puls=false;
    delete buffer_for_Game;
    delete buffer_for_draw;
    delete buffer_for_render;
}
