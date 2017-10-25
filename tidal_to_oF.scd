~lastCycle=0;
~lastDelta=1;
~lastBegin=0;
~lastEnd=1;
~lastFadeTime=0;
~lastGain=1;
~lastN=0;
~lastSpeed=1;

~toOF = NetAddr.new("127.0.0.1", 3333);

(
OSCdef(\oscFromTidal, { |msg|
	MFdef(\oscPostbotin).value(msg);
	// where does this 'n' below comes from???
}, '/play2', n).permanent_(true);
)

MFdef(\oscPostbotin).add(\sendCycle,
	{ |msg|
	msg.collect{ |i|
		if ( ( msg[i]=='cycle') && ( msg[i+1].isFloat ) ){
				~toOF.sendMsg( "/cycle", msg[i+1] );
				"cycle: % ".format( msg[i+1] ).postln;
				~lastCycle = msg[i+1];
			}
		}
	}
);

MFdef(\oscPostbotin).add(\sendDelta,
	{ |msg|
	msg.collect{ |i|
		if ( ( msg[i]=='delta') && ( msg[i+1].isFloat ) && ( msg[i+1] != ~lastDelta ) ){
				~toOF.sendMsg( "/delta", msg[i+1] );
				"delta: % ".format( msg[i+1] ).postln;
				~lastDelta = msg[i+1];
			}
		}
	}
);

MFdef(\oscPostbotin).add(\sendBegin,
	{ |msg|
	msg.collect{ |i|
		if ( (msg[i]=='begin') && (msg[i+1].isFloat) && (msg[i+1] != ~lastBegin) ){
			~toOF.sendMsg("/begin", msg[i+1]);
			"begin: % ".format(msg[i+1]).postln;
			~lastBegin = msg[i+1];
			}
		}
	}
);

MFdef(\oscPostbotin).add(\sendEnd,
	{ |msg|
	msg.collect{ |i|
		if ( (msg[i]=='end') && (msg[i+1].isFloat) && (msg[i+1] != ~lastEnd) ){
			~toOF.sendMsg("/end", msg[i+1]);
			"end: % ".format(msg[i+1]).postln;
			~lastEnd = msg[i+1];
			}
		}
	}
);

MFdef(\oscPostbotin).add(\sendFadeTime,
	{ |msg|
	msg.collect{ |i|
		if ( (msg[i]=='fadeTime') && (msg[i+1].isFloat) && (msg[i+1] != ~lastFadeTime) ){
			~toOF.sendMsg("/fadeTime", msg[i+1]);
			"fade time: % ".format(msg[i+1]).postln;
			~lastFadeTime = msg[i+1];
			}
		}
	}
);

MFdef(\oscPostbotin).add(\sendGain,
	{ |msg|
	msg.collect{ |i|
		if ( (msg[i]=='gain') && (msg[i+1].isFloat) && (msg[i+1] != ~lastGain) ){
			~toOF.sendMsg("/gain", msg[i+1]);
			"gain: % ".format(msg[i+1]).postln;
			~lastGain = msg[i+1];
			}
		}
	}
);

MFdef(\oscPostbotin).add(\sendN,
	{ |msg|
	msg.collect{ |i|
		if ( (msg[i]=='n') && (msg[i+1].isInteger) ){
			~toOF.sendMsg("/n", msg[i+1]);
			"n: % ".format(msg[i+1]).postln;
			~lastN = msg[i+1];
			}
		}
	}
);

MFdef(\oscPostbotin).add(\sendSpeed,
	{ |msg|
	msg.collect{ |i|
		if ( (msg[i]=='speed') && (msg[i+1].isFloat) && (msg[i+1] != ~lastSpeed) ){
			~toOF.sendMsg("/speed", msg[i+1]);
			"speed: % \n".format(msg[i+1]).postln;
			~lastSpeed = msg[i+1];
			}
		}
	}
);

/*
MFdef(\oscPostbotin).remove(\sendDelta);
MFdef(\oscPostbotin).remove(\sendBegin);
MFdef(\oscPostbotin).remove(\sendEnd);
MFdef(\oscPostbotin).remove(\sendFadeTime);
MFdef(\oscPostbotin).remove(\sendGain);
MFdef(\oscPostbotin).remove(\sendN);
MFdef(\oscPostbotin).remove(\sendSpeed);
MFdef(\oscPostbotin).add(\post, { |msg| postf("%\n", msg ); })
MFdef(\oscPostbotin).enable(\post);
MFdef(\oscPostbotin).disable(\post)
OSCdef(\oscFromTidal).disable;
OSCdef(\oscFromTidal).enable;
OSCdef.freeAll;
NetAddr.disconnectAll;
*/

