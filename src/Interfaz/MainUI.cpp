#include <gtkmm.h>
#include <gtkmm/entry.h>
#include <iostream>
#include <string.h>

// CLIENTS
#include "Clients/PadronClient.hpp"

#define UI_FILE "interfazUrna.glade"
//bazel build Executables:PadronServer /proyecto-del-curso-10-4/src/bazel-out/k8-fastbuild/bin/Executables/PadronServer.runfiles File path ../proyecto-del-curso-10-4/PadronPrueba.csv 8082 


Gtk::Window* window1 = nullptr;
Gtk::Window* window2 = nullptr;
Gtk::Button* button1 = nullptr;
Gtk::Button* confButton = nullptr;
Gtk::Button* resetButton = nullptr;
Gtk::Entry* entry1 = nullptr;
Gtk::Entry* entry2 = nullptr;
Gtk::CheckButton* candidato1 = nullptr;
Gtk::CheckButton* candidato2 = nullptr;
Gtk::CheckButton* candidato3 = nullptr;
Gtk::CheckButton* confBox = nullptr;
Gtk::Label* voto = nullptr;
Gtk::Label* aviso = nullptr;
Glib::RefPtr<Gtk::Application> app;


std::string serverPort = "8080";
std::string serverIP = "172.24.3.228";
std::string carnet = "";



/* 
    
  Lo que se ejecuta cuando el boton de Enter es presionado, se verifica con el padron que el carnet ingresado y el codigo hagan match. De hacer match se muestra la ventana de la papeleta

*/
void on_button_clicked()
{
    candidato1->property_active() = 0;
    candidato2->property_active() = 0;
    candidato3->property_active() = 0;
    carnet = entry1->get_text().c_str();
    std::string codigo = entry2->get_text().c_str();


    /* 
    Aqui se crea el cliente del server del padron para verificar que el carnet y el codigo hagan match, si hay match muestra la ventana con la papeleta
    */
    PadronClient client(serverIP, serverPort); 
    std::cout << client.verifyVote(carnet) << std::endl;
    if(client.verifyCode(carnet,codigo) && !client.verifyVote(carnet)){
        window2->show();
        aviso->set_label("Ingrese numero de Carnet y Codigo de verificacion");
    }
    else{
        aviso->set_label("       Datos erroneos, digitelos nuevamente");
    }
    

}

/* 
    
  Lo que se ejecuta cuando el boton de Confirmar Voto es presionado, se verifica la caja de que el votante confirma que el voto es correcto, 
  si es así se le envia al servidor de votos y se actualiza en el servidor del padron que el votante ya realizo el voto

*/
void conf_button_clicked()
{
    int votoCandidato1 = candidato1->property_active();
    int votoCandidato2 = candidato2->property_active();
    int votoCandidato3 = candidato3->property_active();
    int candidatosEscogidos = votoCandidato1 + votoCandidato2 + votoCandidato3;
    std::string eleccion = "";
    
    if(votoCandidato1){
        voto->set_label("Usted seleccionó al candidato 1");
        eleccion = "candidato1";
    }

    if(votoCandidato2){
        voto->set_label("Usted seleccionó al candidato 2");
        eleccion = "candidato2";
    }

    if(votoCandidato3){
        voto->set_label("Usted seleccionó al candidato 3");
        eleccion = "candidato3";
    }

    if(candidatosEscogidos > 1 || candidatosEscogidos==0){
        eleccion = "nulo";
        voto->set_label("Voto nulo seleccionado");
    }

    confBox->show();

     if(confBox->property_active()){
        voto->set_label("Voto enviado, gracias por participar!");
        
    
        candidato1->property_active() = 0;
        candidato2->property_active() = 0;
        candidato3->property_active() = 0;
        resetButton->show();
        confButton->hide();
        confBox->hide();
        confBox->property_active() = 0;
        /* 
    
    
        Aqui se crea el cliente del server de votos para registrar el voto y cliente del server del padron para actualizar que ese votante ya realizó su voto


        */
        PadronClient client(serverIP, serverPort);
        
        client.updateVote(carnet);
      }
     
     
}



/* 
    
  Lo que se ejecuta cuando el boton de Terminar es presionado, se establece todo para que venga el siguiente votante a realizar el voto

*/
void reset_button_clicked()
{
    window2->hide();
    resetButton->hide();
    confButton->show();
    voto->set_label("Voto:");
    entry1->set_text("");
    entry2->set_text("");

}




/* 
    
  Metodo que construye las pestañas y extrae todos lo widgets

*/
void on_app_activate()
{

    // Load the GtkBuilder file and instantiate its widgets:
  auto refBuilder = Gtk::Builder::create();
  try
  {
    refBuilder->add_from_file(UI_FILE);
  }
  catch(const Glib::FileError& ex)
  {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return;
  }
  catch(const Glib::MarkupError& ex)
  {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
    return;
  }
  catch(const Gtk::BuilderError& ex)
  {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return;
  }

    refBuilder->get_widget("interfazUrna1",window1);
  if (!window1)
  {
    std::cerr << "Could not get the dialog" << std::endl;
    return;
  }
   
   refBuilder->get_widget("interfazUrna2",window2);
   if (!window2)
  {
    std::cerr << "Could not get the dialog" << std::endl;
    return;
  }

    refBuilder->get_widget("button1",button1);
    if (button1)
    button1->signal_clicked().connect([] () { on_button_clicked(); });

    refBuilder->get_widget("confButton",confButton);
    if (confButton)
    confButton->signal_clicked().connect([] () { conf_button_clicked(); });

    refBuilder->get_widget("resetButton",resetButton);
    if (resetButton)
    resetButton->signal_clicked().connect([] () { reset_button_clicked(); });
    
    refBuilder->get_widget("entry1",entry1);
    refBuilder->get_widget("entry2",entry2);
    refBuilder->get_widget("candidato1",candidato1);
    refBuilder->get_widget("candidato2",candidato2);
    refBuilder->get_widget("candidato3",candidato3);
    refBuilder->get_widget("confBox",confBox);
    refBuilder->get_widget("voto",voto);
    refBuilder->get_widget("text1",aviso);
    confBox->hide();
    resetButton->hide();
   app->add_window(*window1);
   app->add_window(*window2);
    
   window1->show();

}

int main(int argc, char** argv) {
  app = Gtk::Application::create("interfaz.example");
  app->signal_activate().connect([] () { on_app_activate(); });

  return app->run(argc, argv);
}
