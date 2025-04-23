all: revenue_pb revenue_pc revenue_pd

revenue_pb: revenue_pb.c
	gcc revenue_pb.c -o revenue_pb

revenue_pc: revenue_pc.c
	gcc revenue_pc.c -o revenue_pc

revenue_pd: revenue_pd.c
	gcc revenue_pd.c -o revenue_pd

clean:
	rm revenue_pb revenue_pc revenue_pd