#include <vte/vte.h>
#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>
#include <gdk/gdk.h>

#define CLR_R(x)   (((x) & 0xff0000) >> 16)
#define CLR_G(x)   (((x) & 0x00ff00) >>  8)
#define CLR_B(x)   (((x) & 0x0000ff) >>  0)
#define CLR_16(x)  ((double)(x) / 0xff)
#define CLR_GDK(x) (const GdkRGBA){ .red = CLR_16(CLR_R(x)), \
                                    .green = CLR_16(CLR_G(x)), \
                                    .blue = CLR_16(CLR_B(x)), \
                                    .alpha = 1 }



static gboolean
	on_title_changed(GtkWidget *terminal, gpointer user_data)
	{
		GtkWindow *window = user_data;
		gtk_window_set_title(window, vte_terminal_get_window_title(VTE_TERMINAL(terminal))?:"Terminal");
		return TRUE;
	}


int main(int argc, char* argv[])
{
	
	
	/* Configuration init */
	config_t cfg;
	//const char *str;
	//double bgalpha;
	
	config_init(&cfg);
	
	if(! config_read_file(&cfg, "Byrd.conf"))
	{
		fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
			config_error_line(&cfg), config_error_text(&cfg));
		config_destroy(&cfg);
		return(EXIT_FAILURE);
	}
		double alpha;
		
	if(config_lookup_float(&cfg, "alpha", &alpha))
	{
		printf("Alpha: %6.2f\n", alpha);	
		//bgalpha = alpha;
	}
			
	GtkWidget *window, *terminal;
	/* Init GTK, the window, the term */
	gtk_init(&argc, &argv);
	terminal = vte_terminal_new();
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Byrd");
	
	/* Start new shell */
	gchar **envp = g_get_environ();
	gchar **command = (gchar *[]){g_strdup(g_environ_getenv(envp, "SHELL")), NULL };
	g_strfreev(envp);
	vte_terminal_spawn_async(VTE_TERMINAL(terminal),
			VTE_PTY_DEFAULT,
			NULL,		/* Working dir */
			command, 	/* Command     */
			NULL,		/* Environment */
			0, 		/* Spawn Flags */
			NULL, NULL,	/* Child Setup */
			NULL, 		/* Child PID   */
			-1,		/* Timeout     */
			NULL, NULL, NULL);

	vte_terminal_set_scroll_on_keystroke(VTE_TERMINAL(terminal), TRUE);
	vte_terminal_set_mouse_autohide(VTE_TERMINAL(terminal), TRUE);
	vte_terminal_set_colors(VTE_TERMINAL(terminal),
		&CLR_GDK(0xffffff),
		&(GdkRGBA){ .alpha = 0.35 },
		(const GdkRGBA[]){
			CLR_GDK(0x111111),
			CLR_GDK(0xd36265),
			CLR_GDK(0xaece91),
			CLR_GDK(0xe7e18c),
			CLR_GDK(0x5297cf),
			CLR_GDK(0x963c59),
			CLR_GDK(0x5E7175),
			CLR_GDK(0xbebebe),
			CLR_GDK(0x666666),
			CLR_GDK(0xef8171),
			CLR_GDK(0xcfefb3),
			CLR_GDK(0xfff796),
			CLR_GDK(0x74b8ef),
			CLR_GDK(0xb85e7b),
			CLR_GDK(0xA3BABF),
			CLR_GDK(0xffffff)
	}, 16);
	//vte_terminal_set_color_background(VTE_TERMINAL(terminal), CLR_GDK(0xffffff));

	

	/* Connect Some Signals */
	g_signal_connect(window, "delete-event", gtk_main_quit, NULL);
	g_signal_connect(terminal, "child-exited", gtk_main_quit, NULL);
	g_signal_connect(terminal, "window-title-changed", G_CALLBACK(on_title_changed), GTK_WINDOW(window));

	/* Put Widgets Together and Run Main Loop */
	gtk_container_add(GTK_CONTAINER(window), terminal);
	gtk_widget_show_all(window);
	if(!config_lookup(&cfg, "alpha"))
	{
		gtk_widget_set_opacity(GTK_WIDGET(window), 1);
	}else{
		gtk_widget_set_opacity(GTK_WIDGET(window), alpha);
	}
	gtk_main();
	

}

