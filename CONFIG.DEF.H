static const Lines lines[] = {
        /*
         * you can change the order if you want
         *
         * i also added new line option incase you for
         * some reason dont want it?
         */
        /* text   data              newln */
        { ">os ", name.sysname, "\n" },
        { ">host ", name.nodename, "\n" },
        { ">ker ", name.release, "\n" },
        { ">arc ", name.machine, "\n" }
};
