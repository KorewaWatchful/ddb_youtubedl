#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include <deadbeef/deadbeef.h>
#include <gtk/gtk.h>
#include <deadbeef/gtkui_api.h>



static DB_functions_t *deadbeef;
static DB_misc_t plugin;
static ddb_gtkui_t *gtkui_plugin;

//static gboolean accepting_link();

static int ddb_youtubedl_action_callback(DB_plugin_action_t *action, int ctx){
    printf("lol");
    return 0;
}

static DB_plugin_action_t ddb_youtubedl_action = {
        .title = "File/Add youtube-dl track",
        .name = "ddb_youtubedl_track",
        .flags = DB_ACTION_COMMON | DB_ACTION_ADD_MENU,
        .callback2 = ddb_youtubedl_action_callback,
        .next = NULL,
};

static DB_plugin_action_t* ddb_youtubedl_getactions(DB_playItem_t *it){
    return &ddb_youtubedl_action;
}

int ddb_youtubedl_start(){
    printf("plugin running\n");
    return 0;
}

int ddb_youtubedl_connect() {
    gtkui_plugin = (ddb_gtkui_t *)deadbeef->plug_get_for_id (DDB_GTKUI_PLUGIN_ID);
    if (!gtkui_plugin) {
        fprintf (stderr, "replaygain control: can't find gtkui plugin\n");
        return -1;
    }
    return 0;
}


DB_plugin_t *
ddb_youtubedl_load(DB_functions_t *api){
    deadbeef = api;

    plugin.plugin.api_vmajor = DB_API_VERSION_MAJOR,
    plugin.plugin.api_vminor = DB_API_VERSION_MINOR,
    plugin.plugin.version_major = 1,
    plugin.plugin.version_minor = 12,
    plugin.plugin.type = DB_PLUGIN_MISC,
    plugin.plugin.id = "ddb_youtubedl",
    plugin.plugin.name = "DeaDBeeF Youtube-DL plugin",
    plugin.plugin.descr = "Implements youtube-dl functionality into DeaDBeeF",
    plugin.plugin.copyright =
    "MIT License\n"
    "\n"
    "Copyright (c) 2021 KorewaWatchful\n"
    "\n"
    "Permission is hereby granted, free of charge, to any person obtaining a copy\n"
    "of this software and associated documentation files (the \"Software\"), to deal\n"
    "in the Software without restriction, including without limitation the rights\n"
    "to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n"
    "copies of the Software, and to permit persons to whom the Software is\n"
    "furnished to do so, subject to the following conditions:\n"
    "\n"
    "The above copyright notice and this permission notice shall be included in all\n"
    "copies or substantial portions of the Software.\n"
    "\n"
    "THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n"
    "IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n"
    "FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n"
    "AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n"
    "LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n"
    "OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n"
    "SOFTWARE.\n",
    plugin.plugin.website = "https://github.com/KorewaWatchful/ddb_youtubedl",
    plugin.plugin.start = ddb_youtubedl_start,
    plugin.plugin.connect = ddb_youtubedl_connect,
    plugin.plugin.get_actions = ddb_youtubedl_getactions;

    return DB_PLUGIN(&plugin);
}