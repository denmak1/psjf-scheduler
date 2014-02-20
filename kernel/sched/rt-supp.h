#ifdef CONFIG_RT_GROUP_SCHED
  100+ lines
#else /* CONFIG_RT_GROUP_SCHED */

#define rt_entity_is_task(rt_se) (1)

static inline struct task_struct *rt_task_of(struct sched_rt_entity *rt_se)
{
	return container_of(rt_se, struct task_struct, rt);
}

static inline struct rq *rq_of_rt_rq(struct rt_rq *rt_rq)
{
	return container_of(rt_rq, struct rq, rt);
}

static inline struct rt_rq *rt_rq_of_se(struct sched_rt_entity *rt_se)
{
	struct task_struct *p = rt_task_of(rt_se);
	struct rq *rq = task_rq(p);

	return &rq->rt;
}

void free_rt_sched_group(struct task_group *tg) { }

int alloc_rt_sched_group(struct task_group *tg, struct task_group *parent)
{
	return 1;
}
#endif /* CONFIG_RT_GROUP_SCHED */

#ifdef CONFIG_SMP
  100+ lines
#else

static inline void enqueue_pushable_task(struct rq *rq, struct task_struct *p)
{
}

static inline void dequeue_pushable_task(struct rq *rq, struct task_struct *p)
{
}

static inline
void inc_rt_migration(struct sched_rt_entity *rt_se, struct rt_rq *rt_rq)
{
}

static inline
void dec_rt_migration(struct sched_rt_entity *rt_se, struct rt_rq *rt_rq)
{
}

#endif /* CONFIG_SMP */

#ifdef CONFIG_RT_GROUP_SCHED
  200+ lines
#else /* !CONFIG_RT_GROUP_SCHED */

static inline u64 sched_rt_runtime(struct rt_rq *rt_rq)
{
	return rt_rq->rt_runtime;
}

static inline u64 sched_rt_period(struct rt_rq *rt_rq)
{
	return ktime_to_ns(def_rt_bandwidth.rt_period);
}

typedef struct rt_rq *rt_rq_iter_t;

#define for_each_rt_rq(rt_rq, iter, rq) \
	for ((void) iter, rt_rq = &rq->rt; rt_rq; rt_rq = NULL)

static inline void list_add_leaf_rt_rq(struct rt_rq *rt_rq)
{
}

static inline void list_del_leaf_rt_rq(struct rt_rq *rt_rq)
{
}

#define for_each_leaf_rt_rq(rt_rq, rq) \
	for (rt_rq = &rq->rt; rt_rq; rt_rq = NULL)

#define for_each_sched_rt_entity(rt_se) \
	for (; rt_se; rt_se = NULL)

static inline struct rt_rq *group_rt_rq(struct sched_rt_entity *rt_se)
{
	return NULL;
}

static inline void sched_rt_rq_enqueue(struct rt_rq *rt_rq)
{
	if (rt_rq->rt_nr_running)
		resched_task(rq_of_rt_rq(rt_rq)->curr);
}

static inline void sched_rt_rq_dequeue(struct rt_rq *rt_rq)
{
}

static inline int rt_rq_throttled(struct rt_rq *rt_rq)
{
	return rt_rq->rt_throttled;
}

static inline const struct cpumask *sched_rt_period_mask(void)
{
	return cpu_online_mask;
}

static inline
struct rt_rq *sched_rt_period_rt_rq(struct rt_bandwidth *rt_b, int cpu)
{
	return &cpu_rq(cpu)->rt;
}

static inline struct rt_bandwidth *sched_rt_bandwidth(struct rt_rq *rt_rq)
{
	return &def_rt_bandwidth;
}

#endif /* CONFIG_RT_GROUP_SCHED */

#ifdef CONFIG_SMP
  200+ lines
#else /* !CONFIG_SMP */
static inline int balance_runtime(struct rt_rq *rt_rq)
{
	return 0;
}
#endif /* CONFIG_SMP */

static inline int rt_se_prio(struct sched_rt_entity *rt_se)
{
#ifdef CONFIG_RT_GROUP_SCHED
	struct rt_rq *rt_rq = group_rt_rq(rt_se);

	if (rt_rq)
		return rt_rq->highest_prio.curr;
#endif

	return rt_task_of(rt_se)->prio;
}

#if defined CONFIG_SMP
  ~20 lines
#else /* CONFIG_SMP */

static inline
void inc_rt_prio_smp(struct rt_rq *rt_rq, int prio, int prev_prio) {}
static inline
void dec_rt_prio_smp(struct rt_rq *rt_rq, int prio, int prev_prio) {}

#endif /* CONFIG_SMP */

#if defined CONFIG_SMP || defined CONFIG_RT_GROUP_SCHED
  ~40 lines
#else

static inline void inc_rt_prio(struct rt_rq *rt_rq, int prio) {}
static inline void dec_rt_prio(struct rt_rq *rt_rq, int prio) {}

#endif /* CONFIG_SMP || CONFIG_RT_GROUP_SCHED */

#ifdef CONFIG_RT_GROUP_SCHED
  ~20 lines
#else /* CONFIG_RT_GROUP_SCHED */

static void
inc_rt_group(struct sched_rt_entity *rt_se, struct rt_rq *rt_rq)
{
	start_rt_bandwidth(&def_rt_bandwidth);
}

static inline
void dec_rt_group(struct sched_rt_entity *rt_se, struct rt_rq *rt_rq) {}

#endif /* CONFIG_RT_GROUP_SCHED */
