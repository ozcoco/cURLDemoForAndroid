package org.oz.demo.ui.main;

import org.oz.curl.Test;

/**
 * @ProjectName: cURL-demo
 * @Package: org.oz.demo.ui.main
 * @ClassName: MainModel
 * @Description:
 * @Author: oz
 * @CreateDate: 2020/4/30 16:12
 * @UpdateUser:
 * @UpdateDate: 2020/4/30 16:12
 * @UpdateRemark:
 * @Version: 1.0
 */
public class MainModel implements IMainModel {

    @Override
    public void test(Test.Callback callback) {

        /*Executors.newSingleThreadExecutor().execute(() -> {

            Test t = new Test(callback);
            t.test();

        });*/

        Test t = new Test(callback);
        t.test();

    }
}
