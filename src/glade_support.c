/*
 * Copyright (C) 2006 real_user_name
 * $Id: $
 *
 * This is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Library General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 * $Log: $
 * 
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#if HAVE_GLADE_LIB
#include <glade/glade.h>
#include "widgets.h"
#include "glade_support.h"

/*************************************************************************
 * Static declarations:                                                  *
 *                                                                       *
 *                                                                       *
 *************************************************************************/
typedef struct signal {
	gchar     *name;
	GCallback callback;
} signal;

/*
** Signal handler callbascks.
*/

static void 
on_any_button_clicked(
		GtkButton *widget, 
		gchar     *full_command)
{
	gchar *prefix, *command;
	g_return_if_fail(command != NULL);
#ifdef DEBUG
	g_message("%s(%p, '%s')", __func__, widget, command);
#endif
	command_get_prefix(full_command, &prefix, &command);
	execute_action(widget, command, prefix);
	g_free(command);
	g_free(prefix);
}


static void 
on_any_entry_almost_any(GtkEntry *widget, 
		gchar     *full_command)
{
	gchar *prefix, *command;
	g_return_if_fail(command != NULL);
#ifdef DEBUG
	g_message("%s(%p, '%s')", __func__, widget, command);
#endif
	command_get_prefix(full_command, &prefix, &command);
	execute_action(widget, command, prefix);
	g_free(command);
	g_free(prefix);
}


static void 
on_any_entry_delete_from_cursor(
		GtkEntry *entry, 
		GtkDeleteType *arg1, 
		gint arg2, 
		gpointer user_data) 
{
	on_any_entry_almost_any(entry, user_data);
}

static void 
on_any_entry_insert_at_cursor(
		GtkEntry *entry, 
		gchar *arg1, 
		gpointer user_data)
{
	on_any_entry_almost_any(entry, user_data);
}

static void 
on_any_entry_move_cursor(
		GtkEntry *entry, 
		GtkMovementStep *arg1, 
		gint arg2, 
		gboolean arg3, 
		gpointer user_data)
{
	on_any_entry_almost_any(entry, user_data);
}

static void 
on_any_entry_populate_popup(
		GtkEntry *entry, 
		GtkMenu *arg1, 
		gpointer user_data)
{
	on_any_entry_almost_any(entry, user_data);
}

static void 
on_any_widget_almost_any(
		GtkWidget *widget, 
		gchar *full_command)
{
	gchar *prefix, *command;
	g_return_if_fail(command != NULL);
#ifdef DEBUG
	g_message("%s(%p, '%s')", __func__, widget, command);
#endif
	command_get_prefix(full_command, &prefix, &command);
	execute_action(widget, command, prefix);
	g_free(command);
	g_free(prefix);
}

static gboolean 
on_any_widget_almost_any_gdk_event(
		 GtkWidget *widget, 
		 GdkEvent *event, 
		 gpointer user_data)
{
	on_any_widget_almost_any(widget, user_data);
	return FALSE;
}

#if 0
 /* 
  * GtkWidget unhandled signals.
  */
"can-activate-accel"
 gboolean user_function (GtkWidget *widget, guint signal_id, gpointer user_data)
"child-notify"
 void user_function (GtkWidget *widget, GParamSpec *pspec, gpointer user_data)
"direction-changed"
 void user_function (GtkWidget *widget, GtkTextDirection *arg1, gpointer user_data)
"drag-begin"
 void user_function (GtkWidget *widget, GdkDragContext *drag_context, gpointer user_data)
"drag-data-delete"
 void user_function (GtkWidget *widget, GdkDragContext *drag_context, gpointer user_data)
"drag-data-get"
 void user_function (GtkWidget *widget, GdkDragContext *drag_context, GtkSelectionData *data, guint info, guint time, gpointer user_data)
"drag-data-received"
 void user_function (GtkWidget *widget, GdkDragContext *drag_context, gint x, gint y, GtkSelectionData *data, guint info, guint time, gpointer user_data)
"drag-drop"
 gboolean user_function (GtkWidget *widget, GdkDragContext *drag_context, gint x, gint y, guint time, gpointer user_data)
"drag-end"
 void user_function (GtkWidget *widget, GdkDragContext *drag_context, gpointer user_data)
"drag-leave"
 void user_function (GtkWidget *widget, GdkDragContext *drag_context, guint time, gpointer user_data)
"drag-motion"
 gboolean user_function (GtkWidget *widget, GdkDragContext *drag_context, gint x, gint y, guint time, gpointer user_data)
"focus"
 gboolean user_function (GtkWidget *widget, GtkDirectionType *arg1, gpointer user_data)
"grab-notify"
 void user_function (GtkWidget *widget, gboolean was_grabbed, gpointer user_data)
"hierarchy-changed"
 void user_function (GtkWidget *widget, GtkWidget *widget2, gpointer user_data)
"mnemonic-activate"
 gboolean user_function (GtkWidget *widget, gboolean arg1, gpointer user_data)
"parent-set"
 void user_function (GtkWidget *widget, GtkObject *old_parent, gpointer user_data)
"screen-changed"
 void user_function (GtkWidget *widget, GdkScreen *arg1, gpointer user_data)
"selection-get"
 void user_function (GtkWidget *widget, GtkSelectionData *data, guint info, guint time, gpointer user_data)
"selection-received"
 void user_function (GtkWidget *widget, GtkSelectionData *data, guint time, gpointer user_data)
"show-help"
 gboolean user_function (GtkWidget *widget, GtkWidgetHelpType *arg1, gpointer user_data)
"size-allocate"
 void user_function (GtkWidget *widget, GtkAllocation *allocation, gpointer user_data)
"size-request"
 void user_function (GtkWidget *widget, GtkRequisition *requisition, gpointer user_data)
"state-changed"
 void user_function (GtkWidget *widget, GtkStateType state, gpointer user_data)
"style-set"
 void user_function (GtkWidget *widget, GtkStyle *previous_style, gpointer user_data)
"window-state-event"
 gboolean user_function (GtkWidget *widget, GdkEventWindowState *event, gpointer user_data)
#endif 

/*
** Signal handler connectors for each widget types we support.
*/
static gboolean
find_and_connect_handler(
		GtkWidget *widget,
		signal *signals,
		const gchar *signal_name,
		const gchar *handler_name)
{
	gint n;
	
	for (n = 0; signals[n].name != NULL; ++n) {
		if (g_ascii_strcasecmp(signals[n].name, signal_name) == 0)
			g_signal_connect(G_OBJECT(widget), 
					signal_name, 
					signals[n].callback, 
					g_strdup(handler_name));
			return TRUE;
	}

	return FALSE;
}


static gboolean
gtk_toggle_button_signal_handler_connector(
		const gchar *handler_name, 
		GObject *object, 
		const gchar *signal_name, 
		const gchar *signal_data, 
		GObject *connect_object, 
		gboolean after, 
		gpointer user_data)
{
	/*
	 * As I see, the "toggle" function is the very same as of the "clicked"
	 * signal of the normal buttons.
	 */
	if (g_ascii_strcasecmp(signal_name, "toggled") == 0) {
		g_signal_connect(object, 
				signal_name, 
				G_CALLBACK(on_any_button_clicked), 
				g_strdup(handler_name));
		return TRUE;
	}
	return FALSE;
}

static gboolean
gtk_button_signal_handler_connector(
		const gchar *handler_name, 
		GObject *object, 
		const gchar *signal_name, 
		const gchar *signal_data, 
		GObject *connect_object, 
		gboolean after, 
		gpointer user_data)
{
	gint n;
	gchar *signal_names[] = {
		"activate", "clicked", "enter", "leave", "pressed",
		"released", NULL
	};

	for (n = 0; signal_names[n] != NULL; ++n) {
		if (g_ascii_strcasecmp(signal_name, signal_names[n]) == 0) {
			g_signal_connect(object, 
					signal_names[n], 
					G_CALLBACK(on_any_button_clicked), 
					g_strdup(handler_name));
			return TRUE;
		}
	}
	return FALSE;
}

static gboolean
gtk_entry_signal_handler_connector(
		const gchar *handler_name, 
		GObject *object, 
		const gchar *signal_name, 
		const gchar *signal_data, 
		GObject *connect_object, 
		gboolean after, 
		gpointer user_data)
{
	gint n;
	signal entry_signals[] = {
		{ "activate",           (GCallback)on_any_entry_almost_any },
		{ "backspace",          (GCallback)on_any_entry_almost_any },
		{ "copy-clipboard",     (GCallback)on_any_entry_almost_any },
		{ "cut-clipboard",      (GCallback)on_any_entry_almost_any },
		{ "paste-clipboard",    (GCallback)on_any_entry_almost_any },
		{ "toggle-overwrite",   (GCallback)on_any_entry_almost_any },
		{ "delete-from-cursor", (GCallback)on_any_entry_delete_from_cursor },
		{ "insert-at-cursor",   (GCallback)on_any_entry_insert_at_cursor },
		{ "move-cursor",        (GCallback)on_any_entry_move_cursor },
		{ "populate-popup",     (GCallback)on_any_entry_populate_popup },
		{ NULL,                 (GCallback)NULL }
	};

	return find_and_connect_handler(GTK_WIDGET(object), 
			entry_signals, 
			signal_name,
			handler_name);
}

static gboolean
gtk_widget_signal_handler_connector(
		const gchar *handler_name, 
		GObject *object, 
		const gchar *signal_name, 
		const gchar *signal_data, 
		GObject *connect_object, 
		gboolean after, 
		gpointer user_data)
{
	variable *var;
	signal widget_signals[] = {
		{ "accel-closures-changed",    (GCallback)on_any_widget_almost_any },
		{ "composited-changed",        (GCallback)on_any_widget_almost_any },
		{ "grab-focus",                (GCallback)on_any_widget_almost_any },
		{ "hide",                      (GCallback)on_any_widget_almost_any },
		{ "map",                       (GCallback)on_any_widget_almost_any },
		{ "popup-menu",                (GCallback)on_any_widget_almost_any },
		{ "show",                      (GCallback)on_any_widget_almost_any },
		{ "unmap",                     (GCallback)on_any_widget_almost_any },
		{ "unrealize",                 (GCallback)on_any_widget_almost_any },
		{ "button-press-event",        (GCallback)on_any_widget_almost_any_gdk_event },
		{ "client-event",              (GCallback)on_any_widget_almost_any_gdk_event },
		{ "configure-event",           (GCallback)on_any_widget_almost_any_gdk_event },
		{ "delete-event",              (GCallback)on_any_widget_almost_any_gdk_event },
		{ "destroy-event",             (GCallback)on_any_widget_almost_any_gdk_event },
		{ "enter-notify-event",        (GCallback)on_any_widget_almost_any_gdk_event },
		{ "event",                     (GCallback)on_any_widget_almost_any_gdk_event },
		{ "event-after",               (GCallback)on_any_widget_almost_any_gdk_event },
		{ "expose-event",              (GCallback)on_any_widget_almost_any_gdk_event },
		{ "focus-in-event",            (GCallback)on_any_widget_almost_any_gdk_event },
		{ "focus-out-event",           (GCallback)on_any_widget_almost_any_gdk_event },
		{ "grab-broken-event",         (GCallback)on_any_widget_almost_any_gdk_event },
		{ "key-press-event",           (GCallback)on_any_widget_almost_any_gdk_event },
		{ "key-relese-event",          (GCallback)on_any_widget_almost_any_gdk_event },
		{ "leave-notify-event",        (GCallback)on_any_widget_almost_any_gdk_event },
		{ "map-event",                 (GCallback)on_any_widget_almost_any_gdk_event },
		{ "motion-notify-event",       (GCallback)on_any_widget_almost_any_gdk_event },
		{ "no-expose-event",           (GCallback)on_any_widget_almost_any_gdk_event },
		{ "property-notify-event",     (GCallback)on_any_widget_almost_any_gdk_event },
		{ "proximity-in-event",        (GCallback)on_any_widget_almost_any_gdk_event },
		{ "proximity-out-event",       (GCallback)on_any_widget_almost_any_gdk_event },
		{ "scroll-event",              (GCallback)on_any_widget_almost_any_gdk_event },
		{ "selection-clear-event",     (GCallback)on_any_widget_almost_any_gdk_event },
		{ "selection-notify-event",    (GCallback)on_any_widget_almost_any_gdk_event },
		{ "selection-request-event",   (GCallback)on_any_widget_almost_any_gdk_event },
		{ "unmap-event",               (GCallback)on_any_widget_almost_any_gdk_event },
		{ "visibility-notify-event",   (GCallback)on_any_widget_almost_any_gdk_event },
		{ NULL,                        (GCallback)NULL }
	};
	/*
	 * The best thing to do is to register this callback as the input
	 * attribute of the given variable. We can't connect the signal to a
	 * signal handler, for it is already created.
	 */
	if (g_ascii_strcasecmp(signal_name, "realize") == 0) {
		var = find_variable_by_widget(GTK_WIDGET(object));
		/*
		 * We should always find this variable.
		 */
		g_return_val_if_fail(var != NULL, FALSE);
		attributeset_insert(var->Attributes, ATTR_INPUT, handler_name);
		return TRUE;
	}
	
	return find_and_connect_handler(GTK_WIDGET(object), 
			widget_signals, 
			signal_name,
			handler_name);
}


/*
 */
static void 
signal_handler_connector(
		const gchar *handler_name, 
		GObject *object, 
		const gchar *signal_name, 
		const gchar *signal_data, 
		GObject *connect_object, 
		gboolean after, 
		gpointer user_data)
{
#ifdef DEBUG
	g_message("%s(): start", __func__);
	g_message("      signal_name: '%s'", signal_name);
	g_message("     handler_name: '%s'", handler_name);
	//g_message("           object: %p", object);
	//g_message("      signal_data: '%s' <------", signal_data);
	//g_message("   connect_object: '%p'", connect_object);
	//g_message("        user_data: '%s'", user_data);
#endif
	if (GTK_IS_ENTRY(object))
		if (gtk_entry_signal_handler_connector(handler_name, 
					object,
					signal_name,
					signal_data,
					connect_object,
					after,
					user_data))
			return;
	
	if (GTK_IS_TOGGLE_BUTTON(object))
		if (gtk_toggle_button_signal_handler_connector(handler_name, 
					object,
					signal_name,
					signal_data,
					connect_object,
					after,
					user_data))
			return;

	if (GTK_IS_BUTTON(object))
		if (gtk_button_signal_handler_connector(handler_name, 
					object,
					signal_name,
					signal_data,
					connect_object,
					after,
					user_data))
			return;
	
	if (GTK_IS_TOOL_BUTTON(object))
		if (gtk_button_signal_handler_connector(handler_name,
					object,
					signal_name,
					signal_data,
					connect_object,
					after,
					user_data))
			return;
	/*
	 * Some thing is obviously missing.
	 */
	if (GTK_IS_WIDGET(object))
		if (gtk_widget_signal_handler_connector(handler_name, 
				object,
				signal_name,
				signal_data,
				connect_object,
				after,
				user_data))
			return;

	g_warning("%s(): Unhandled signal: '%s'", __func__, signal_name);
		
}


static void
register_widgets(GladeXML *glade_xml)
{
	GList        *widget_list, *li;
	GtkWidget    *widget;
	AttributeSet *Attr;
	gint          type;
	const gchar  *name;

	widget_list = glade_xml_get_widget_prefix(glade_xml, "");
	for (li = widget_list; li != NULL; li = li->next) {
		widget = li->data;
		name = gtk_widget_get_name(li->data);
		Attr = attributeset_new();
		attributeset_set_if_unset(Attr, ATTR_VARIABLE, name);
		type = widget_get_type_from_pointer(widget);
		variables_new_with_widget(Attr, NULL, widget, type);
#ifdef DEBUG
		g_message("%s(): widget name: %s, type: %d", 
				__func__, name, type);
#endif
	}
	g_list_free(widget_list);
}

static void
refresh_widgets(GladeXML *glade_xml)
{
	GList        *widget_list, *li;
	GtkWidget    *widget;
	AttributeSet *Attr;
	gint          type;
	const gchar  *name;

	widget_list = glade_xml_get_widget_prefix(glade_xml, "");
	for (li = widget_list; li != NULL; li = li->next) {
		widget = li->data;
		name = gtk_widget_get_name(li->data);
		variables_refresh(name);
	}

	g_list_free(widget_list);
}

/*************************************************************************
 * Public functions:                                                     *
 *                                                                       *
 *                                                                       *
 *************************************************************************/
void
run_program_by_glade(
		const gchar *filename,
		const gchar *window_name) 
{
	GladeXML  *glade_xml;
	GtkWidget *main_window;

	glade_init();	
	glade_xml = glade_xml_new(filename, NULL, PACKAGE);
	if (window_name != NULL)
		main_window = glade_xml_get_widget(glade_xml, window_name);
	else
		main_window = glade_xml_get_widget(glade_xml, "MAIN_WINDOW");

	if (main_window == NULL)
		g_error("Can not load '%s' from file '%s'", window_name,
				filename);
	/*
	 *
	 */
	register_widgets(glade_xml);
	/*
	 * Connecting the signals.
	 */
	glade_xml_signal_autoconnect_full(glade_xml,
			(GladeXMLConnectFunc) signal_handler_connector,
			NULL);
	gtk_signal_connect(GTK_OBJECT(main_window), "delete_event",
			   GTK_SIGNAL_FUNC(window_delete_event_handler), NULL);
	
	refresh_widgets(glade_xml);
	
	gtk_widget_show(main_window);
	gtk_main();
}
#endif

