package test;

import sample.Common;
import sample.ExternSample;
import sample.ExternShared;
import unittest.TestCase;

class SampleUnitTest extends TestCase
{
    public function testCommonHaxeBackend()
    {
        assertEquals("Common Haxe backend", new Common().hi());
    }

    public function testSeparateExterns()
    {
        assertEquals("do one thing in here", new ExternSample().doOneThing());
    }

    public function testSharedExterns()
    {
        assertEquals("do one other thing", ExternShared.doOneOtherThing());
    }
}
