package org.oz.demo.ui.main

import android.content.Context
import androidx.test.ext.junit.runners.AndroidJUnit4
import androidx.test.platform.app.InstrumentationRegistry
import org.junit.Test
import org.junit.runner.RunWith

import static org.junit.Assert.assertEquals

/**
 *
 * @ProjectName: cURL-demo
 * @Package: org.oz.demo.ui.main* @ClassName: MainViewModelTest* @Description:
 * @Author:         oz
 * @CreateDate: 2020/4/29 9:51
 * @UpdateUser:
 * @UpdateDate:     2020/4/29 9:51
 * @UpdateRemark:
 * @Version:        1.0
 */
@RunWith(AndroidJUnit4.class)
class MainViewModelTest {

    @Test
    public void useAppContext() {
        // Context of the app under test.
        Context appContext = InstrumentationRegistry.getInstrumentation().getTargetContext();

        assertEquals("org.oz.demo", appContext.getPackageName());
    }
}
