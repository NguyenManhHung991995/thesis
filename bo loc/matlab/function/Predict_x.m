function x_p=Predict_x(x_c,T)% x_p: x predicted, x_c: x_corrected
C3=[0,-x_c(3),x_c(2);x_c(3),0,-x_c(1);-x_c(2),x_c(1),0];
Ak=[eye(3,3),T*C3;zeros(3,3),eye(3,3)];
x_p=Ak*x_c;
end