osrwdmpnp.inf: $(TARGETEXEFILES)
    copy $(TARGETEXEFILES) .
    wustamp -a -l -o osrwdmpnp.inf
    rm /f $(TARGETNAME).$(TARGETEXT)

