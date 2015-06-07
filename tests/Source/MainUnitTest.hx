import test.SampleUnitTest;
import unittest.implementations.TestHTTPLogger;
import unittest.implementations.TestJUnitLogger;
import unittest.implementations.TestSimpleLogger;

import unittest.TestRunner;

import duell.DuellKit;

class MainUnitTest
{
    static function main()
    {
        DuellKit.initialize(start);
    }

    static function start() : Void
    {
        var r = new TestRunner(testComplete, DuellKit.instance().onError);
        r.add(new SampleUnitTest());

#if test

    #if jenkins
        r.addLogger(new TestHTTPLogger(new TestJUnitLogger()));
    #else
        r.addLogger(new TestHTTPLogger(new TestSimpleLogger()));
    #end

#else
        r.addLogger(new TestSimpleLogger());
#end

        r.run();
    }

    static function testComplete()
    {

    }

}
